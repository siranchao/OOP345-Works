/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_CENTRALUNIT_H__
#define SDDS_CENTRALUNIT_H__
#include <string>
#include <fstream>
#include <exception>
#include <functional>
#include "Job.h"
namespace sdds {
	class Job;

	template<typename T>
	class CentralUnit {
	public:
		std::ostream& log = std::cout;
	private:
		std::string m_type{};
		T** m_items{};
		Job* m_jobs[4]{};
		size_t m_size{};
		size_t m_count{};

	public:
		CentralUnit();
		CentralUnit(std::string unitType, const char* unitName);
		//rule of five
		virtual ~CentralUnit();
		CentralUnit(const CentralUnit<T>& src);
		CentralUnit<T>& operator=(const CentralUnit<T>& src) = delete;
		CentralUnit(CentralUnit<T>&& src);
		CentralUnit<T>& operator=(CentralUnit<T>&& src);
		CentralUnit<T>& operator+=(std::string jobName);
		bool has_jobs()const;
		int get_available_units()const;
		//upgrade
		void run();
		CentralUnit<T>& operator+=(T* unit);
		T* operator[](const char* jobTitle)const;
		void display()const;
		static void complete_job(CentralUnit<T>& cpu, T* unit);
		
	private:
		std::string& trim(std::string& str)const;
		void operator~();
	};

	template<typename T>
	CentralUnit<T>::CentralUnit(){ 
		//default
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(std::string workType, const char* fileName) : m_type{workType} {
		std::ifstream fs(fileName);
		if (!fs) {
			throw std::invalid_argument("File cannot be opened.");
		}
		else {
			//start to count
			std::string str;
			while (!fs.eof()) {
				getline(fs, str);
				m_size++;
			}
			m_items = new T* [m_size];

			//start to read
			fs.seekg(0, std::ios::beg);
			std::string unitType, unitName, workCap;
			size_t capacity, i = 0;
			while (!fs.eof()) {
				getline(fs, str);
				//read 1st
				unitType = str.substr(0, str.find("|"));
				trim(unitType);
				str = str.erase(0, str.find("|") + 1);
				//read 2nd
				unitName = str.substr(0, str.find("|"));
				trim(unitName);
				str = str.erase(0, str.find("|") + 1);
				//read 3rd
				try {
					workCap = str.substr(0, str.find("|"));
					trim(workCap);
					capacity = std::stoul(workCap);
				}
				catch (const std::exception& err) {
					capacity = 1;
				}
				//construct processing units
				m_items[i] = new T(this, unitType, unitName, capacity);

				m_items[i]->on_complete(CentralUnit<T>::complete_job);
				m_items[i]->on_error([&](T* unit)->void {
					auto jobPtr = unit->free();
					log << "Failed to complete job" << jobPtr->name() << std::endl;
					log << get_available_units() << " units available" << std::endl;
					delete jobPtr;
				});

				i++;
			}
			fs.close();
		}
	}

	template<typename T>
	CentralUnit<T>::~CentralUnit() {
		~*this;
		delete[] m_items;
	}

	template<typename T>
	std::string& CentralUnit<T>::trim(std::string& str)const {
		while (str[0] == ' ') {
			str.erase(0, str.find_first_not_of(' '));
		}
		while (str[str.size() - 1] == ' ') {
			str.erase(str.find_last_not_of(' ') + 1);
		}
		return str;
	}

	template<typename T>
	void CentralUnit<T>::operator~() {
		//clear job queue
		if (m_count > 0) {
			for (size_t i = 0; i < m_count; i++) {
				delete m_jobs[i];
				m_jobs[i] = nullptr;
			}
		}
		//clear unit list
		if (m_size > 0) {
			for (size_t i = 0; i < m_size; i++) {
				delete m_items[i];
				m_items[i] = nullptr;
			}
		}
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(const CentralUnit<T>& src) {
		throw std::runtime_error("Error");
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(CentralUnit<T>&& src) {
		*this = std::move(src);
	}
	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator=(CentralUnit<T>&& src) {
		if (this != &src) {
			~*this;
			log = src.log;
			m_type = src.m_type;
			m_size = src.m_size;
			m_count = src.m_count;
			//move copy
			m_items = src.m_items;
			for (size_t i = 0; i < 4; i++) {
				m_jobs[i] = src.m_jobs[i];
				src.m_jobs[i] = nullptr;
			}
			//clear src
			src.m_items = nullptr;
			src.m_size = 0;
			src.m_count = 0;
		}
		return *this;
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(std::string jobName) {
		if (m_count < 4) {
			m_jobs[m_count] = new Job(jobName);
			m_count++;
			return *this;
		}
		else {
			throw std::string("Job queue is full");
		}
	}

	template<typename T>
	void CentralUnit<T>::run() {
		if (m_size > 0) {
			for (size_t i = 0; i < m_size; i++) {
				if (!*m_items[i] && m_count > 0) {
					*m_items[i] += m_jobs[m_count - 1];
					m_jobs[m_count - 1] = nullptr;
					m_count--;
				}
				if (*m_items[i]) {
					m_items[i]->run();
				}
			}
		}
	}

	template<typename T>
	bool CentralUnit<T>::has_jobs()const {
		bool found = false;
		for (size_t i = 0; i < m_size && !found; i++) {
			if (*m_items[i]) found = true;
		}
		return found || m_count > 0;
	}

	template<typename T>
	int CentralUnit<T>::get_available_units()const {
		int val = 0;
		for (size_t i = 0; i < m_size; i++) {
			if (!*m_items[i]) val++;
		}
		return val;
	}

	//template<typename T>
	//void CentralUnit<T>::complete_job(CentralUnit<T>& cpu, T* unit) {
	//	auto jobPtr = unit->free();
	//	cpu.log << "[COMPLETE] " << *jobPtr << " using " << *unit << std::endl;
	//	cpu.log << get_available_units() << " units available." << std::endl;
	//	delete jobPtr;
	//}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(T* unit) {
		if (unit) {
			//resize the array
			T** temp = new T* [m_size + 1];
			for (size_t i = 0; i < m_size; i++) {
				temp[i] = m_items[i];
			}
			delete[] m_items;
			m_items = temp;
			m_items[m_size] = unit;
			m_size++;
			//assign callbacks
			//m_items[m_size]->on_complete(&complete_job);
			//m_items[m_size]->on_error([&](T* unit)->void {
			//	auto jobPtr = unit->free();
			//	log << "Failed to complete job" << jobPtr->name() << std::endl;
			//	log << get_available_units() << " units available" << std::endl;
			//	delete jobPtr;
			//});
		}
		else {
			throw std::runtime_error("Error");
		}
		return *this;
	}

	template<typename T>
	T* CentralUnit<T>::operator[](const char* jobTitle)const {
		T* val{};
		std::string str;
		bool found = false;
		for (size_t i = 0; i < m_size && !found; i++) {
			if (*m_items[i]) {
				str = m_items[i]->get_current_job()->name();
			}
			if (strcmp(jobTitle, str.c_str()) == 0) {
				found = true;
			}
			val = m_items[i];
		}
		if (found) {
			return val;
		}
		else {
			throw std::out_of_range("Job is not being handled by a unit.");
		}
	}

	template<typename T>
	void CentralUnit<T>::display()const {
		log << "Central " << m_type << " Unit list" << std::endl;
		for (size_t i = 0; i < m_size; i++) {
			log << "[000" << i + 1 << "] " << *m_items[i] << std::endl;
		}
	}

	template<typename T>
	void CentralUnit<T>::complete_job(CentralUnit<T>& cpu, T* unit) {
		auto jobPtr = unit->free();
		cpu.log << "[COMPLETE] " << *jobPtr << " using " << *unit << std::endl;
		cpu.log << cpu.get_available_units() << " units available." << std::endl;
		delete jobPtr;
	}



}
#endif // !SDDS_CENTRALUNIT_H__

