#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>
#include <exception>
#include <cmath>

namespace sdds {
	template<typename T>
	class GeneratingList {
		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the valadity of SIN No's
		bool checksin(const std::string& sin) const {
			bool val = false;
			bool isnumber = true;
			for (const char& c : sin) {
				if (isdigit(c) == 0) isnumber = false;
			}

			if (isnumber) {
				int sum{}, k{};
				for (size_t i = 0; i < sin.size(); i++) {
					k = sin[i] - '0';
					k *= (i % 2 == 0) ? 1 : 2;
					if (k >= 10) k = k % 10 + floor(k / 10);
					sum += k;
				}
				if (sum % 10 == 0) val = true;
			}
			else {
				throw std::string("SIN contains other characters");
			}
			return val;
		}

		//TODO: Overload the += operator with a smart pointer as a second operand.
		void operator+=(std::unique_ptr<T> ptr) {
			list.push_back(*ptr);
		}
		

		//TODO: Overload the += operator with a raw pointer as a second operand.
		void operator+=(T* ptr) {
			list.push_back(*ptr);
		}
		
		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
