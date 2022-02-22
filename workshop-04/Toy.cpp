#include <iostream>
#include <string>
#include "Toy.h"

namespace sdds {
	const double Toy::m_HST = 0.13;

	Toy::Toy() : m_orderId{ 0 }, m_name{ "" }, m_numItems{ 0 }, m_price{0.0} {
		//default
	}

	Toy::Toy(const std::string& toy) {
		std::string record = toy;
		std::string id, name, num, price;
		//id
		id = record.substr(0, record.find(":"));
		record = record.erase(0, record.find(":") + 1);
		//name
		name = record.substr(0, record.find(":"));
		record = record.erase(0, record.find(":") + 1);
		//num
		num = record.substr(0, record.find(":"));
		record = record.erase(0, record.find(":") + 1);
		//price
		price = record.substr(0, record.find(":"));

		m_orderId = std::stoul(trim(id));
		m_name = trim(name);
		m_numItems = std::stoi(trim(num));
		m_price = std::stod(trim(price));
	}

	void Toy::update(int numItems) {
		m_numItems = numItems;
	}

	Toy::~Toy() {
		//default
	}

	std::ostream& Toy::display(std::ostream& os)const {
		os.setf(std::ios::fixed);
		os.precision(2);
		os << "Toy";
		os.width(8);
		os << m_orderId << ":";
		os.width(18);
		os << m_name;
		os.width(3);
		os << m_numItems << " items";
		os.width(8);
		os << m_price << "/item  subtotal:";
		os.width(7);
		os << m_price * m_numItems << " tax:";
		os.width(6);
		os << m_price * m_numItems * m_HST << " total:";
		os.width(7);
		os << m_price * m_numItems * (1 + m_HST) << std::endl;
		os.precision(6);
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Toy& src) {
		return src.display(os);
	}

	std::string& Toy::trim(std::string& str)const {
		while (str[0] == ' ') {
			str.erase(0, str.find_first_not_of(' '));
		}
		while (str[str.size() - 1] == ' ') {
			str.erase(str.find_last_not_of(' ') + 1);
		}
		return str;
	}

}