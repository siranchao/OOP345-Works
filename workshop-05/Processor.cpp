/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <iostream>
#include "Processor.h"

namespace sdds {
	Processor::Processor() {
		//default
	}

	Processor::Processor(CentralUnit<Processor>* host, std::string unitType, std::string unitName, size_t capacity) {
		m_host = host;
		m_brand = unitType;
		m_code = unitName;
		m_power = capacity;
		//on_complete();
		//on_error();
	}

	void Processor::run() {
		//if (m_host && *this) {
		//	if (m_current->is_complete()) {
		//		//cleared and removed from this processor
		//		delete m_current;
		//		m_current = nullptr;
		//	}
		//	else {
		//		try {
		//			(*m_current)(m_power);
		//		}
		//		catch (...) {
		//			m_host->log << "Processed over quota for " << *m_current << std::endl;
		//			//clearing and removing the job assigned to this processor
		//			delete m_current;
		//			m_current = nullptr;
		//		}
		//	}
		//}
		if (!m_current->is_complete()) {
			try {
				(*m_current)(m_power);
				if (m_current->is_complete()) {
					m_fnObj1(*m_host, this);
				}
			}
			catch (std::underflow_error& e) {
				m_fnObj2(this);
			}
		}
	}

	Processor::operator bool()const {
		return m_current != nullptr;
	}

	Processor& Processor::operator+=(Job* jobPtr) {
		if (*this) {
			throw std::string("Job already assigned");
		}
		else {
			m_current = jobPtr;
		}
		return *this;
	}

	Job* Processor::get_current_job()const {
		return m_current;
	}

	Processor::~Processor() {
		//default
	}

	//upgrade
	void Processor::on_complete(void (*fnObj1)(CentralUnit<Processor>& host, Processor* processor)) {
		m_fnObj1 = fnObj1;
	}
	void Processor::on_error(std::function<void(Processor* processor)> fnObj2) {
		m_fnObj2 = fnObj2;
	}

	//void Processor::on_complete() {
	//	m_fnObj1 = &complete_job;
	//}
	//void Processor::on_error() {
	//	m_fnObj2 = [&](Processor* unit)->void {
	//		auto jobPtr = unit->free();
	//		m_host->log << "Failed to complete job " << jobPtr->name() << std::endl;
	//		m_host->log << m_host->get_available_units() << " units available." << std::endl;
	//		delete jobPtr;
	//	};
	//}

	void Processor::operator()() {
		if (*this && !m_current->is_complete()) {
			//try {
			//	(*m_current)(m_power);
			//}
			//catch (...) {
			//	m_host->log << "Processed over quota for " << *m_current << std::endl;
			//	//clearing and removing the job assigned to this processor
			//	delete m_current;
			//	m_current = nullptr;
			//}
			(*m_current)(m_power);

			if (m_current->is_complete()) {
				try {
					m_fnObj1(*m_host, this);
				}
				catch (std::underflow_error& e) {
					m_fnObj2(this);
				}
			}
		}
	}

	Job* Processor::free() {
		auto val = m_current;
		m_current = nullptr;
		return val;
	}

	std::ostream& Processor::display(std::ostream& os)const {
		os << "(" << m_power << ") " << m_brand << " " << m_code;
		if (*this) {
			os << " processing " << *m_current;
		}
		//else {
		//	os << std::endl;
		//}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Processor& src) {
		return src.display(os);
	}





}