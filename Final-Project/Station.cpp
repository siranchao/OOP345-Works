// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/03/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Utilities.h"
#include "Station.h"

namespace sdds {
   size_t Station::m_widthField = 0;
   size_t Station::id_generator = 0;

   Station::Station() {
      //default
      id_generator++;
   }
   Station::~Station() {
      //default
   }

   Station::Station(const std::string& record) {
      id_generator++;
      if (record != "") {
         Utilities helper{};
         size_t next_pos = 0;
         bool more = true;
         m_id = Station::id_generator;
         m_item = helper.extractToken(record, next_pos, more);
         m_serialNum = std::stoul(helper.extractToken(record, next_pos, more));
         m_stock = std::stoul(helper.extractToken(record, next_pos, more));
         if (m_widthField < helper.getFieldWidth())  m_widthField = helper.getFieldWidth();
         m_desc = helper.extractToken(record, next_pos, more);
      }
   }

   void Station::display(std::ostream& os, bool full) const {
      os << std::setfill('0') << std::setw(3) << m_id << " | ";
      os.setf(std::ios::left);
      os << std::setfill(' ') << std::setw(m_widthField + 1) << m_item << " | ";
      os.unsetf(std::ios::left);
      os << std::setfill('0') << std::setw(6) << m_serialNum << std::setfill(' ');
      if (full) {
         os << " | " << std::setw(4) << m_stock << " | " << m_desc << std::endl;
      }
      else {
         os << " | " << std::endl;
      }
   }

   const std::string& Station::getItemName() const {
      return m_item;
   }

   size_t Station::getNextSerialNumber() {
      return m_serialNum++;
   }

   size_t Station::getQuantity() const {
      return m_stock;
   }

   void Station::updateQuantity() {
      if (m_stock > 0) m_stock--;
   }


}