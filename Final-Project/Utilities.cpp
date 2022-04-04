// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/03/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <exception>
#include <iostream>
#include "Utilities.h"

namespace sdds {
   char Utilities::m_delimiter{};

   Utilities::Utilities() : m_widthField{1} {
      //default
   }
   Utilities::~Utilities() {
      //default
   }

   void Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth()const {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      std::string val{};
      if (more) {
         if (str[next_pos] != m_delimiter) {
            val = str.substr(next_pos, str.find(m_delimiter, next_pos + 1) - next_pos);
            trim(val);
            if (m_widthField < val.size()) m_widthField = val.size();
           
            if (str.find(m_delimiter, next_pos + 1) != std::string::npos) {
               next_pos = str.find(m_delimiter, next_pos + 1) + 1;
               more = true;
            }
            else {
               next_pos = 0;
               more = false;
            }
         }
         else {
            more = false;
            throw std::string("delimiter is found at next_pos");
         }
      }
      return val;
   }

   void Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }
   char Utilities::getDelimiter() {
      return m_delimiter;
   }

}