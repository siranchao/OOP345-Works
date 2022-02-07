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
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
namespace sdds {

	template<typename T, size_t CAPACITY>
	class Collection {

		T m_arr[CAPACITY]{};
		size_t m_size;
		static T m_dummy;
	
	public:
		Collection();
		virtual ~Collection();

		size_t size()const;
		std::ostream& display(std::ostream& os = std::cout)const;
		virtual bool add(const T& item);
		T operator[](size_t index)const;

	};

	template<typename T, size_t CAPACITY>
	T Collection<T, CAPACITY>::m_dummy{};

	template<>
	Pair Collection<Pair, 100>::m_dummy{ "No Key", "No Value" };

	template<typename T, size_t CAPACITY>
	Collection<T, CAPACITY>::Collection() : m_size{0} {
		//default constructor
	}

	template<typename T, size_t CAPACITY>
	Collection<T, CAPACITY>::~Collection() {
		//empty
	}

	template<typename T, size_t CAPACITY>
	size_t Collection<T, CAPACITY>::size()const {
		return m_size;
	}

	template<typename T, size_t CAPACITY>
	std::ostream& Collection<T, CAPACITY>::display(std::ostream& os)const {
		if (os) {
			os << "----------------------" << std::endl;
			os << "| Collection Content |" << std::endl;
			os << "----------------------" << std::endl;
			//os.setf(std::ios::left);
			for (size_t i = 0; i < m_size; i++) {
				os << m_arr[i] << std::endl;
			}
			os << "----------------------" << std::endl;
		}
		return os;
	}

	template<typename T, size_t CAPACITY>
	bool Collection<T, CAPACITY>::add(const T& item) {
		bool res = false;
		if (m_size < CAPACITY) {
			m_arr[m_size] = item;
			m_size++;
			res = true;
		}
		return res;
	}

	template<typename T, size_t CAPACITY>
	T Collection<T, CAPACITY>::operator[](size_t index)const {
		return (index >= 0 && index < m_size) ? m_arr[index] : m_dummy;
	}


}



#endif // !SDDS_COLLECTION_H

