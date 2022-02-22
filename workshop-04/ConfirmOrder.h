#ifndef SDDS_CONFIRMORDER_H__
#define SDDS_CONFIRMORDER_H__
#include <iostream>
namespace sdds {
	class Toy;

	class ConfirmOrder {
		const sdds::Toy** m_toys{};
		size_t m_numOfToys;

	public:
		ConfirmOrder();
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);
		std::ostream& display(std::ostream& os = std::cout)const;

		//rule of five
		virtual ~ConfirmOrder();
		ConfirmOrder(const ConfirmOrder& src);
		ConfirmOrder& operator=(const ConfirmOrder& src);
		ConfirmOrder(ConfirmOrder&& src);
		ConfirmOrder& operator=(ConfirmOrder&& src);

	private:
		void operator~();
	};

	std::ostream& operator<<(std::ostream& os, const ConfirmOrder& src);


}
#endif // !SDDS_CONFIRMORDER_H__

