// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <deque>
#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds {
   size_t CustomerOrder::m_widthField = 0;

   CustomerOrder::CustomerOrder() {
      //default
   }

   CustomerOrder::CustomerOrder(const std::string& str) {
      if (str != "") {
         //start reading string
         Utilities helper{};
         std::deque<std::string> items;
         size_t next_pos = 0;
         bool more = true;
         while (more) {
            items.push_back(helper.extractToken(str, next_pos, more));
         }

         m_name = items.front();
         items.pop_front();
         m_product = items.front();
         items.pop_front();
         if (m_widthField < helper.getFieldWidth())  m_widthField = helper.getFieldWidth();
         m_cntItem = items.size();
         m_itemList = new Item* [m_cntItem];
         //initiate dynamic array
         for (size_t i = 0; i < m_cntItem; i++) {
            m_itemList[i] = new Item(items[i]);
         }
      }
   }

   CustomerOrder::CustomerOrder(const CustomerOrder&) {
      throw std::string("Copy constructor not allowed");
   }
   CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
      *this = std::move(src);
   }
   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
      if (this != &src) {
         for (size_t i = 0; i < m_cntItem; i++) {
            delete m_itemList[i];
         }
         delete[] m_itemList;
         m_itemList = src.m_itemList;
         m_name = src.m_name;
         m_product = src.m_product;
         m_cntItem = src.m_cntItem;
         src.m_itemList = nullptr;
         src.m_cntItem = 0;
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder() {
      for (size_t i = 0; i < m_cntItem; i++) {
         delete m_itemList[i];
      }
      delete [] m_itemList;
   }

   bool CustomerOrder::isOrderFilled()const {
      bool filled = true;
      for (size_t i = 0; i < m_cntItem && filled; i++) {
         if (!m_itemList[i]->m_isFilled) filled = false;
      }
      return filled;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName)const {
      bool found = false;
      bool val = true;
      std::vector<Item*> matchedItems;
      for (size_t i = 0; i < m_cntItem; i++) {
         if (m_itemList[i]->m_itemName == itemName) {
            found = true;
            matchedItems.push_back(m_itemList[i]);
         }
      }

      //if item found
      if (found) {
         val = std::all_of(matchedItems.begin(), matchedItems.end(), [](const Item* ptr) {return ptr->m_handled == true; });
      }

      return val;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {
      bool flag = true;
      for (size_t i = 0; i < m_cntItem && flag; i++) {

         if (m_itemList[i]->m_itemName == station.getItemName() && !m_itemList[i]->m_handled) {
            flag = false;
            if (station.getQuantity() > 0) {
               //fill the item
               station.updateQuantity();
               m_itemList[i]->m_isFilled = true;
               m_itemList[i]->m_handled = true;
               m_itemList[i]->m_serialNum = station.getNextSerialNumber();
               os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
            }
            else {
               for (size_t k = 0; k < m_cntItem; k++) {
                  if (m_itemList[k]->m_itemName == station.getItemName() && !m_itemList[k]->m_handled) {
                     m_itemList[k]->m_handled = true;
                     os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << std::endl;
                  }
               }
            }
         }
      }
   }

   void CustomerOrder::display(std::ostream& os)const {
      os << m_name << " - " << m_product << std::endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[" << std::setw(6) << std::setfill('0') << m_itemList[i]->m_serialNum << "] " << std::setfill(' ');
         os.setf(std::ios::left);
         os << std::setw(m_widthField) << m_itemList[i]->m_itemName << "   - ";
         os.unsetf(std::ios::left);
         if (m_itemList[i]->m_isFilled) {
            os << "FILLED" << std::endl;
         }
         else {
            os << "TO BE FILLED" << std::endl;
         }
      }
   }


}