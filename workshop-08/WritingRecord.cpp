#include <exception>
#include <memory>
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		for (size_t i = 0; i < emp.size(); i++) {
			bool found = false;
			double salary{};
			for (size_t k = 0; k < sal.size() && !found; k++) {
				if (emp[i].id == sal[k].id) {
					found = true;
					salary = sal[k].salary;
				}
			}

			if (found) {
				EmployeeWage* ptr = new EmployeeWage(emp[i].name, salary);
				try {
					ptr->rangeValidator();
				}
				catch (const string& msg) {
					delete ptr;
					throw msg;
				}

				if (emp.checksin(emp[i].id)) {
					activeEmp += ptr;
				}
				else {
					delete ptr;
					throw std::string("Invalid SIN");
				}
				delete ptr;
			}
		}
		return activeEmp;
	}

	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		for (size_t i = 0; i < emp.size(); i++) {
			bool found = false;
			double salary{};
			for (size_t k = 0; k < sal.size() && !found; k++) {
				if (emp[i].id == sal[k].id) {
					found = true;
					salary = sal[k].salary;
				}
			}

			if (found) {
				std::unique_ptr<EmployeeWage> ptr(new EmployeeWage(emp[i].name, salary));
				ptr->rangeValidator();
				if (emp.checksin(emp[i].id)) {
					activeEmp += ptr.get();
				}
				else {
					throw std::string("Invalid SIN");
				}
				ptr.reset();
			}
		}
		return activeEmp;
	}
}


