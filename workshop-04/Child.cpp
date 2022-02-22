#include <iostream>
#include "Child.h"
#include "Toy.h"

namespace sdds {

	Child::Child() : m_name{ "" }, m_age{ 0 }, m_size{0} {
		//default
	}

	Child::Child(std::string name, int age, const Toy* toys[], size_t count) : m_name{ name }, m_age{age} {
		m_size = count;
		m_toyPtrs = new const sdds::Toy* [m_size];
		for (size_t i = 0; i < m_size; i++) {
			m_toyPtrs[i] = new Toy(*toys[i]);
		}
	}
	
	size_t Child::size()const {
		return m_size;
	}

	std::ostream& Child::display(std::ostream& os)const {
		static int CALL_CNT = 0;
		os << "--------------------------" << std::endl;
		os << "Child " << ++CALL_CNT << ": " << m_name << " " << m_age << " years old:" << std::endl;
		os << "--------------------------" << std::endl;
		if (m_size == 0) {
			os << "This child has no toys!" << std::endl;
		}
		else {
			for (size_t i = 0; i < m_size; i++) {
				os << *m_toyPtrs[i];
			}
		}
		os << "--------------------------" << std::endl;
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Child& src) {
		return src.display(os);
	}

	void Child::operator~() {
		for (size_t i = 0; i < m_size; i++) {
			delete m_toyPtrs[i];
			m_toyPtrs[i] = nullptr;
		}
		delete[] m_toyPtrs;
		m_toyPtrs = nullptr;
		m_size = 0;
	}

	//rule of five

	Child::~Child() {
		for (size_t i = 0; i < m_size; i++) {
			delete m_toyPtrs[i];
			m_toyPtrs[i] = nullptr;
		}
		delete[] m_toyPtrs;
	}
	Child::Child(const Child& src) {
		m_name = src.m_name;
		m_age = src.m_age;
		m_size = src.m_size;
		m_toyPtrs = new const sdds::Toy * [m_size];
		for (size_t i = 0; i < m_size; i++) {
			m_toyPtrs[i] = new Toy(*src.m_toyPtrs[i]);
		}
	}
	Child& Child::operator=(const Child& src) {
		if (this != &src) {
			~*this;
			m_name = src.m_name;
			m_age = src.m_age;
			m_size = src.m_size;
			m_toyPtrs = new const sdds::Toy* [m_size];
			for (size_t i = 0; i < m_size; i++) {
				m_toyPtrs[i] = new Toy(*src.m_toyPtrs[i]);
			}
		}
		return *this;
	}
	Child::Child(Child&& src) {
		m_name = src.m_name;
		m_age = src.m_age;
		m_size = src.m_size;
		m_toyPtrs = src.m_toyPtrs;
		src.m_size = 0;
		src.m_name = "";
		src.m_age = 0;
		src.m_toyPtrs = nullptr;
	}
	Child& Child::operator=(Child&& src) {
		if (this != &src) {
			~*this;
			m_name = src.m_name;
			m_age = src.m_age;
			m_size = src.m_size;
			m_toyPtrs = src.m_toyPtrs;
			src.m_size = 0;
			src.m_name = "";
			src.m_age = 0;
			src.m_toyPtrs = nullptr;
		}
		return *this;
	}



}