#include <iostream>
#include "ConfirmOrder.h"
#include "Toy.h"

namespace sdds{

	ConfirmOrder::ConfirmOrder() : m_numOfToys{0} {
		//default
	}

	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
		bool add = true;
		for (size_t i = 0; i < m_numOfToys && add; i++) {
			if (m_toys[i] == &toy) add = false;
		}
		if (add) {
			const sdds::Toy** temp = new const sdds::Toy* [m_numOfToys + 1];
			for (size_t i = 0; i < m_numOfToys; i++) {
				temp[i] = m_toys[i];
			}
			temp[m_numOfToys] = &toy;
			delete[] m_toys;
			m_toys = temp;
			m_numOfToys++;
		}
		return *this;
	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
		if (m_numOfToys > 0) {
			bool found = false;
			size_t index = 0;
			for (size_t i = 0; i < m_numOfToys && !found; i++) {
				if (m_toys[i] == &toy) {
					m_toys[i] = nullptr;
					found = true;
					index = i;
				}
			}
			if (found) {
				for (size_t j = index; j < m_numOfToys - 1; j++) {
					m_toys[j] = m_toys[j + 1];
				}
				m_toys[m_numOfToys - 1] = nullptr;
				m_numOfToys--;
			}
		}
		return *this;
	}

	std::ostream& ConfirmOrder::display(std::ostream& os)const {
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send" << std::endl;
		os << "--------------------------" << std::endl;
		if (m_numOfToys == 0) {
			os << "There are no confirmations to send!" << std::endl;
		}
		else {
			for (size_t i = 0; i < m_numOfToys; i++) {
				os << *m_toys[i];
			}
		}
		os << "--------------------------" << std::endl;
		return os;
	}


	std::ostream& operator<<(std::ostream& os, const ConfirmOrder& src) {
		return src.display(os);
	}

	void ConfirmOrder::operator~() {
		delete[] m_toys;
		m_toys = nullptr;
		m_numOfToys = 0;
	}

	//rule of five
	ConfirmOrder:: ~ConfirmOrder() {
		delete[] m_toys;
	}
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& src) {
		*this = src;
	}
	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& src) {
		if (this != &src) {
			~*this;
			m_numOfToys = src.m_numOfToys;
			m_toys = new const sdds::Toy* [m_numOfToys];
			for (size_t i = 0; i < m_numOfToys; i++) {
				m_toys[i] = src.m_toys[i];
			}
		}
		return *this;
	}
	ConfirmOrder::ConfirmOrder(ConfirmOrder&& src) {
		*this = std::move(src);
	}
	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& src) {
		if (this != &src) {
			~*this;
			m_numOfToys = src.m_numOfToys;
			m_toys = src.m_toys;
			src.m_numOfToys = 0;
			src.m_toys = nullptr;
		}
		return *this;
	}





}