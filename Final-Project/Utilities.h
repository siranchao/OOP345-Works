// Name: Siran Cao
// Seneca Student ID: 159235209
// Seneca email: scao34@myseneca.ca
// Date of completion: 04/03/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

namespace sdds {

	class Utilities {
		size_t m_widthField;
		static char m_delimiter;

	public:
		Utilities();
		virtual ~Utilities();

		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth()const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

	private:
		std::string trim(std::string& str)const {
			while (str[0] == ' ') {
				str.erase(0, str.find_first_not_of(' '));
			}
			while (str[str.size() - 1] == ' ') {
				str.erase(str.find_last_not_of(' ') + 1);
			}
			return str;
		}
	};



}

#endif // !SDDS_UTILITIES_H

