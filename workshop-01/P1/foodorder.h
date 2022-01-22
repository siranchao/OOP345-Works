/*
Name: Siran Cao
Email: scao34@myseneca.ca
Student ID: 159235209
Data: 01/20/2022
Section: OOP345-NBB
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SDDS_FOODORDER_H
#define SDDS_FOODORDER_H

extern double g_taxrate;
extern double g_dailydiscount;

namespace sdds {
	class FoodOrder {
		char m_customerName[10];
		char* m_foodDesc{};
		double m_foodPrice;
		bool m_special;

	public:
		FoodOrder();
		FoodOrder(const FoodOrder& src);
		FoodOrder& operator=(const FoodOrder& src);
		std::istream& read(std::istream& is = std::cin);
		std::ostream& display(std::ostream& os = std::cout)const;
		~FoodOrder();

	private:
		operator bool()const;
		static void alloCopy(char*& des, const char* src);
	};

}



#endif // !SDDS_FOODORDER_H
