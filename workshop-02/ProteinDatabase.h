#ifndef SDDS_PROTEINDATABASE_H
#define SDDS_PROTEINDATABASE_H
#include <string>

namespace sdds {

	class ProteinDatabase {
		std::string* m_proteinArr{};
		size_t m_size = 0;
	
	public:
		ProteinDatabase();
		ProteinDatabase(const char* fileName);
		//rule of 5
		ProteinDatabase(const ProteinDatabase& src);
		ProteinDatabase& operator=(const ProteinDatabase& src);
		ProteinDatabase(ProteinDatabase&& src); //move constructor
		ProteinDatabase& operator=(ProteinDatabase&& src); //move assignment
		virtual ~ProteinDatabase();

		size_t size()const;
		std::string operator[](size_t)const;

	private:
		void readFile(const char* fileName);
		void operator~();
	};


}



#endif // !SDDS_PROTEINDATABASE_H

