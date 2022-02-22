/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_PROCESSOR_H__
#define SDDS_PROCESSOR_H__
#include "CentralUnit.h"

namespace sdds {

	class Processor {
	private:
		CentralUnit<Processor>* m_host{};
		std::string m_brand{};
		std::string m_code{};
		size_t m_power{};
		Job* m_current{};
	public:
		void (*m_fnObj1)(CentralUnit<Processor>& host, Processor* processor) = nullptr;
		std::function<void(Processor* processor)> m_fnObj2;

	public:
		Processor();
		Processor(CentralUnit<Processor>* host, std::string unitType, std::string unitName, size_t capacity);
		void run();
		operator bool()const;
		Processor& operator+=(Job* jobPtr);
		Job* get_current_job()const;
		virtual ~Processor();

		//upgrade
		//void on_complete(void (*fnObj1)(CentralUnit<Processor>& host, Processor* processor));
		//void on_error(std::function<void(Processor* processor)> fnObj2);
		void on_complete();
		void on_error();
		void operator()();
		Job* free();
		std::ostream& display(std::ostream& os = std::cout)const;
	};

	std::ostream& operator<<(std::ostream& os, const Processor& src);
	void complete_job(CentralUnit<Processor>& cpu, Processor* unit);

}
#endif // !SDDS_PROCESSOR_H__

