#include <iostream>
#include <fstream>
#include "ProteinDatabase.h"

namespace sdds {

	ProteinDatabase::ProteinDatabase() {
		//default-empty
	}
	ProteinDatabase::ProteinDatabase(const char* fileName) {
		readFile(fileName);
	}

	size_t ProteinDatabase::size()const {
		return m_size;
	}

	std::string ProteinDatabase::operator[](size_t index)const {
		std::string str = (index < m_size) ? m_proteinArr[index] : "";
		return str;
	}


	void ProteinDatabase::readFile(const char* fileName) {
		std::ifstream ifstr(fileName);
		std::string temp;
		if (ifstr) {
			//count line numbers
			while (getline(ifstr, temp, '\n')) {
				if (temp[0] == '>') m_size++;
			}

			// allocate read into dyn array
			if (m_size > 0) {
				ifstr.clear();
				ifstr.seekg(0);
				m_proteinArr = new std::string[m_size];
				
				int index = -1;
				while (getline(ifstr, temp, '\n')) {
					if (temp[0] == '>') {
						index++;
					}
					else {
						m_proteinArr[index] += temp;
					}
				}
			}
		}
	}

	void ProteinDatabase::operator~() {
		delete[] m_proteinArr;
		m_proteinArr = nullptr;
		m_size = 0;
	}


	////rule of five

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& src) {
		operator=(src);
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src) {
		if (this != &src) {
			~*this;
			m_size = src.m_size;
			m_proteinArr = new std::string[m_size];
			for (size_t i = 0; i < m_size; i++) {
				m_proteinArr[i] = src.m_proteinArr[i];
			}
		}
		return *this;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) {
		operator=(std::move(src));
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) {
		if (this != &src) {
			~*this;
			m_size = src.m_size;
			m_proteinArr = src.m_proteinArr;
			src.m_proteinArr = nullptr;
			src.m_size = 0;
		}
		return *this;
	}

	ProteinDatabase:: ~ProteinDatabase() {
		delete[] m_proteinArr;
		m_proteinArr = nullptr;
	}

















}