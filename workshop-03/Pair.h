/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/06/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H
#include <string>

namespace sdds {

	class Pair {
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() {
			return m_key;
		}
		const std::string& getValue() {
			return m_value;
		}
		Pair(const std::string& key = "", const std::string& value = "");

		std::ostream& display(std::ostream& os = std::cout)const;

		bool operator==(const Pair& ro);

	};
	std::ostream& operator<<(std::ostream& os, const Pair& src);


}

#endif 






