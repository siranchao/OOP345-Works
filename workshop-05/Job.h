/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#ifndef SDDS_JOB_H__
#define SDDS_JOB_H__
#include <cstring>
#include <string>
namespace sdds {

	class Job {
		std::string m_name{};
		size_t m_totalUnits{};
		size_t m_remianUnits{};
		bool m_active;

	public:
		Job();
		Job(std::string title);
		virtual ~Job();
		bool is_active()const;
		bool is_complete()const;
		std::string name()const;
		std::ostream& display(std::ostream& os = std::cout)const;
		void operator()(size_t handledWork);

	};

	std::ostream& operator<<(std::ostream& os, const Job& src);






}
#endif // !SDDS_JOB_H__

