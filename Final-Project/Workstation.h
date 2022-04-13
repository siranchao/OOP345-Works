// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/12/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
namespace sdds {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation: public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_nextStation{};

	public:
		Workstation();
		Workstation(const std::string& record);
		virtual ~Workstation();
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation()const;
		void display(std::ostream& os)const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};


}

#endif // !SDDS_WORKSTATION_H
