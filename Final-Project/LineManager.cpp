// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/12/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include <iostream>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
   LineManager::LineManager() {
      //default
   }
   LineManager::~LineManager() {
      //default
   }

   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
      try {
         //read file
         std::ifstream fs(file);
         if (!fs) throw std::string("Unable to open file");
         std::string record;
         std::vector<std::string> records;
         while (!fs.eof()) {
            std::getline(fs, record);
            records.push_back(record);
         }
         fs.close();

         //process active & next
         std::string active;
         std::string next;
         Utilities helper;
         std::vector<std::string> nexts;
         for (auto& line : records) {
            size_t next_pos = 0;
            bool more = true;
            active = helper.extractToken(line, next_pos, more);
            next = more ? helper.extractToken(line, next_pos, more) : "";
            auto iterActive = std::find_if(stations.begin(), stations.end(), [=](const Workstation* ptr) {return ptr->getItemName() == active; });
            auto iterNext = std::find_if(stations.begin(), stations.end(), [=](const Workstation* ptr) {return ptr->getItemName() == next; });

            //set m_activeLine and nextSation for each element
            if (iterActive != stations.end()) {
               m_activeLine.push_back(*iterActive);
               (*iterActive)->setNextStation((iterNext != stations.end()) ? *iterNext : nullptr);
            }
            if (next != "") nexts.push_back(next);
         }

         //find m_firstStation
         for (auto& ele : m_activeLine) {
            if (std::none_of(nexts.begin(), nexts.end(), [&](const std::string str) {return str == ele->getItemName(); })) {
               m_firstStation = ele;
            }
         }
         m_cntCustomerOrder = g_pending.size();
      }
      catch (...) {
         throw std::string("There is an error when constructing LineManager.cpp");
      }

   }

   void LineManager::reorderStations() {
      std::vector<Workstation*> temp;
      temp.push_back(m_firstStation);
      while (temp.back()->getNextStation()) {
         auto iter = std::find(m_activeLine.begin(), m_activeLine.end(), temp.back()->getNextStation());
         temp.push_back(*iter);
      }
      m_activeLine = temp;
   }

   bool LineManager::run(std::ostream& os) {
      static int count = 1;
      os << "Line Manager Iteration: " << count++ << std::endl;

      if (g_pending.size() > 0) {
         (*m_firstStation) += std::move(g_pending.front());
         g_pending.pop_front();
      }
      std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr) {ptr->fill(os);});

      std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ptr) {ptr->attemptToMoveOrder();});

      return (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) ? true : false;
   }

   void LineManager::display(std::ostream& os)const {
      for (auto& ele : m_activeLine) {
         ele->display(os);
      }
   }



}