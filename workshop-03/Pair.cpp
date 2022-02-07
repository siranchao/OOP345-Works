/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/06/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include "Pair.h"

namespace sdds {

	Pair::Pair(const std::string& key, const std::string& value) : m_key{key}, m_value{value} {
		//default constructor
	}

	std::ostream& Pair::display(std::ostream& os)const {
		if (os) {
			os.width(20);
			os << m_key << ": " << m_value;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Pair& src) {
		return src.display(os);
	}

	bool Pair::operator==(const Pair& ro) {
		return (m_key == ro.m_key) ? true : false;
	}





}