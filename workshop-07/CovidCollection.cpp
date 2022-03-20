
#include <fstream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "CovidCollection.h"
namespace sdds {
   CovidCollection::CovidCollection() {
      //default
   }
   CovidCollection::CovidCollection(std::string fileName) {
      std::fstream fs(fileName);
      if (!fs) {
         throw std::invalid_argument("File cannot be opened.");
      }
      else {
         //read file
         Covid rec{};
         std::string line{};
         while (!fs.eof()) {
            getline(fs, line);
            if (line != "") {
               rec.m_country = trim(line.substr(0, 25));
               rec.m_city = trim(line.substr(25, 25));
               rec.m_variant = trim(line.substr(50, 25));
               rec.m_year = std::stoi(trim(line.substr(75, 5)));
               rec.m_caseNum = std::stoul(trim(line.substr(80, 5)));
               rec.m_deaths = std::stoul(trim(line.substr(85, 5)));
               m_collection.push_back(rec);
            }
         }
         fs.close();
      }
   }
   CovidCollection::~CovidCollection() {
      //default
   }

   void CovidCollection::display(std::ostream& out)const {
      std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& ele) {out << ele << std::endl; });
      size_t caseSum = 0, deathSum = 0;
      std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& ele) {caseSum += ele.m_caseNum; });
      std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& ele) {deathSum += ele.m_deaths; });
      out.fill('-');
      out << std::setw(88) << "" << std::endl;
      out.fill(' ');
      out << "|" << std::setw(49) << " " << "Total Cases Around the World:  " << caseSum << " |" << std::endl;
      out << "|" << std::setw(48) << " " << "Total Deaths Around the World:  " << deathSum << " |" << std::endl;
   }

   std::string CovidCollection::trim(std::string str)const {
      while (str[0] == ' ') {
         str.erase(0, str.find_first_not_of(' '));
      }
      while (str[str.size() - 1] == ' ') {
         str.erase(str.find_last_not_of(' ') + 1);
      }
      return str;
   }

   std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
      out << "| " << std::left << std::setw(21) << theCovid.m_country << " | ";
      out << std::left << std::setw(15) << theCovid.m_city << " | ";
      out << std::left << std::setw(20) << theCovid.m_variant << " | ";
      out.unsetf(std::ios::left);
      if (theCovid.m_year < 0) {
         out << std::setw(6) << "" << " | ";
      }
      else {
         out << std::setw(6) << theCovid.m_year << " | ";
      }
      out << std::setw(4) << theCovid.m_caseNum << " | ";
      out << std::setw(3) << theCovid.m_deaths << " |";
      return out;
   }

   void CovidCollection::sort(std::string field) {
      if (field == "country") {
         std::sort(m_collection.begin(), m_collection.end(), [](const Covid& a, const Covid& b) {return a.m_country < b.m_country; });
      }
      else if (field == "variant") {
         std::sort(m_collection.begin(), m_collection.end(), [](const Covid& a, const Covid& b) {return a.m_variant < b.m_variant; });
      }
      else if (field == "cases") {
         std::sort(m_collection.begin(), m_collection.end(), [](const Covid& a, const Covid& b) {return a.m_caseNum < b.m_caseNum; });
      }
      else if (field == "deaths") {
         std::sort(m_collection.begin(), m_collection.end(), [](const Covid& a, const Covid& b) {return a.m_deaths < b.m_deaths; });
      }
      else {
         throw std::invalid_argument("Wrong sorting field.");
      }
   }

   void CovidCollection::cleanList() {
      auto it = std::find_if(m_collection.begin(), m_collection.end(), [](const Covid& ele) {return ele.m_variant == "[None]"; });
      while (it != m_collection.end()) {
         it->m_variant = "";
         it = std::find_if(m_collection.begin(), m_collection.end(), [](const Covid& ele) {return ele.m_variant == "[None]"; });
      }
   }

   bool CovidCollection::inCollection(std::string varName)const {
      auto val = std::any_of(m_collection.begin(), m_collection.end(), [=](const Covid& ele) {return ele.m_variant == varName; });
      return val;
   }

   std::list<Covid> CovidCollection::getListForCountry(std::string country)const {
      std::list<Covid> val {};
      std::copy_if(m_collection.begin(), m_collection.end(), std::inserter(val, val.begin()), [=](const Covid& ele) {return ele.m_country == country; });
      return val;
   }

   std::list<Covid> CovidCollection::getListForVariant(std::string variant)const {
      std::list<Covid> val{};
      std::copy_if(m_collection.begin(), m_collection.end(), std::inserter(val, val.begin()), [=](const Covid& ele) {return ele.m_variant == variant; });
      return val;
   }
}