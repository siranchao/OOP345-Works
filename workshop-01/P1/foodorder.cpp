/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 01/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "foodorder.h"

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

using namespace std;
namespace sdds {
	
	FoodOrder::operator bool()const {
		return m_customerName[0] ? true : false;
	}

	FoodOrder::FoodOrder() {
		m_customerName[0] = '\0';
		m_foodPrice = 0.0;
		m_special = false;
	}
	FoodOrder::~FoodOrder() {
		delete[] m_foodDesc;
	}
	FoodOrder::FoodOrder(const FoodOrder& src) {
		operator=(src);
	}

	FoodOrder& FoodOrder::operator=(const FoodOrder& src) {
		if (this != &src) {
			alloCopy(m_foodDesc, src.m_foodDesc);
			strcpy(m_customerName, src.m_customerName);
			m_foodPrice = src.m_foodPrice;
			m_special = src.m_special;
		}
		return *this;
	}

	istream& FoodOrder::read(istream& is) {
		if (is) {
			string read;
			is.getline(m_customerName, 10, ',');
			getline(is, read, ',');
			alloCopy(m_foodDesc, read.c_str());
			is >> m_foodPrice;
			is.ignore();
			m_special = (is.peek() == 'Y') ? true : false;
			is.ignore(100, '\n');
		}
		return is;
	}

	ostream& FoodOrder::display(ostream& os)const {
		static int counter = 0;
		if (*this) {
			os.setf(ios::left);
			os.setf(ios::fixed);
			os.width(2);
			os << ++counter << ". ";
			os.width(10);
			os << m_customerName << '|';
			os.width(25);
			os << m_foodDesc << '|';
			os.width(12);
			os.precision(2);
			os << m_foodPrice * (1.0 + g_taxrate) << '|';
			os.unsetf(ios::left);
			if (m_special) {
				os.width(13);
				os << m_foodPrice * (1.0 + g_taxrate) - g_dailydiscount;
			}
			os << endl;
		}
		else {
			os.setf(ios::left);
			os.width(2);
			os << ++counter << ". ";
			os << "No Order" << endl;
			os.unsetf(ios::left);
		}
		return os;
	}


	void FoodOrder::alloCopy(char*& des, const char* src) {
		delete[] des;
		des = nullptr;
		des = new char[strlen(src) + 1];
		strcpy(des, src);
	}


}