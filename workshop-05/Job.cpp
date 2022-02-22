/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <iostream>
#include <exception>
#include "Job.h"

namespace sdds {

	Job::Job() : m_active{false} {
      //default
   }
	Job::Job(std::string title) : m_name{title} {
		m_totalUnits = title.size() % 10 + 1;
		m_remianUnits = m_totalUnits;
		m_active = true;
	}
	Job::~Job() {
		//default
	}

	bool Job::is_active()const {
		return m_active;
	}
	bool Job::is_complete()const {
		return m_remianUnits == 0;
	}
	std::string Job::name()const {
		return m_name;
	}
	std::ostream& Job::display(std::ostream& os)const {
		os << '`' << m_name << "` [";
		os.fill('0');
		os.width(2);
		os << m_remianUnits << '/';
		os.width(2);
		os << m_totalUnits << " remaining]";
		os.fill(' ');
		return os;
 	}

	void Job::operator()(size_t handledWork) {
		if (handledWork > m_remianUnits) {
			m_remianUnits = 0;
			throw std::underflow_error("Error");
		}
		else if (handledWork == m_remianUnits) {
			m_remianUnits -= handledWork;
			m_active = false;
		}
		else {
			m_remianUnits -= handledWork;
		}
	}


	std::ostream& operator<<(std::ostream& os, const Job& src) {
		return src.display(os);
	}
}
