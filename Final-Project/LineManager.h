// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/12/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <vector>
#include "Workstation.h"
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
namespace sdds {

	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:
		LineManager();
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		virtual ~LineManager();

		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os)const;
	};


}
#endif // !SDDS_LINEMANAGER_H
