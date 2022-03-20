#ifndef SDDS_COVIDCOLLECTION_H__
#define SDDS_COVIDCOLLECTION_H__
#include <string>
#include <vector>
#include <list>
namespace sdds {

	struct Covid {
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		size_t m_caseNum{};
		size_t m_deaths{};
		int m_year{};
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};

	public:
		CovidCollection();
		CovidCollection(std::string fileName);
		void display(std::ostream& out)const;
		virtual ~CovidCollection();
		void sort(std::string field);
		void cleanList();
		bool inCollection(std::string varName) const;
		std::list<Covid> getListForCountry(std::string country)const;
		std::list<Covid> getListForVariant(std::string variant)const;
	private:
		std::string trim(std::string str)const;
	};

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);



}

#endif // !SDDS_COVIDCOLLECTION_H__

