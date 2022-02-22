#ifndef SDDS_TOY_H__
#define SDDS_TOY_H__
#include <string>

namespace sdds {

	class Toy {
		size_t m_orderId;
		std::string m_name;
		int m_numItems;
		double m_price;
		static const double m_HST;

	public:
		Toy();
		Toy(const std::string& toy);
		void update(int numItems);
		virtual ~Toy();
		std::ostream& display(std::ostream& os = std::cout)const;

	private:
		std::string& trim(std::string& str)const;

	};

	std::ostream& operator<<(std::ostream& os, const Toy& src);





}

#endif // !SDDS_TOY_H__
