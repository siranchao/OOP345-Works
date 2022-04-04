// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/03/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
namespace sdds {

	class Station {
		int m_id{};
		std::string m_item{};
		std::string m_desc{};
		size_t m_serialNum{};
		size_t m_stock{};

		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station();
		virtual ~Station();
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};


}

#endif // !SDDS_STATION_H
