/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 02/06/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include "Collection.h"
#ifndef SDDS_SET_H
#define SDDS_SET_H

namespace sdds {

	template<typename T>
	class Set: public Collection<T, 100> {
	public:
		Set();
		virtual ~Set();
		bool add(const T& item);

	};

	template<typename T>
	Set<T>::Set() {
		//default constructor
	}

	template<typename T>
	Set<T>::~Set() {
		//empty
	}

	template<typename T>
	bool Set<T>::add(const T& item) {
		bool res = false;
		if (Collection<T, 100>::size() < 100) {
			bool flag = false;
			for (size_t i = 0; i < Collection<T, 100>::size() && !flag; i++) {
				if (Collection<T, 100>::operator[](i) == item) flag = true;
			}

			if (!flag) {
				res = Collection<T, 100>::add(item);
			}
		}
		return res;
	}

	template<>
	bool Set<double>::add(const double& item) {
		bool res = false;
		if (Collection<double, 100>::size() < 100) {
			bool flag = false;
			for (size_t i = 0; i < Collection<double, 100>::size() && !flag; i++) {
				if (std::abs(Collection<double, 100>::operator[](i) - item) <= 0.01) flag = true;
			}

			if (!flag) {
				res = Collection<double, 100>::add(item);
			}
		}
		return res;
	}




}

#endif // !SDDS_SET_H

