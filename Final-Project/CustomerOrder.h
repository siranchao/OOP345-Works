// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>
#include "Station.h"
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
namespace sdds {

	struct Item {
		std::string m_itemName;
		size_t m_serialNum{ 0 };
		bool m_isFilled{ false };
		bool m_handled{ false };
		Item(const std::string& src) : m_itemName{ src } {
			//item constructor
		};
	};

	class CustomerOrder {

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{0};
		Item** m_itemList{};

		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		virtual ~CustomerOrder();
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;

		bool isOrderFilled()const;
		bool isItemFilled(const std::string& itemName)const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os)const;
	};

}

#endif // !SDDS_CUSTOMERORDER_H
