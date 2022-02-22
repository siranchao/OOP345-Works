#ifndef SDDS_CHILD_H__
#define SDDS_CHILD_H__
#include <string>

namespace sdds {
	class Toy;

	class Child {
		std::string m_name;
		int m_age;
		const sdds::Toy** m_toyPtrs{};
		size_t m_size;

	public:
		Child();
		Child(std::string name, int age, const Toy* toys[], size_t count);
		size_t size()const;
		std::ostream& display(std::ostream& os = std::cout)const;

		//rule of five
		virtual ~Child();
		Child(const Child& src);
		Child& operator=(const Child& src);
		Child(Child&& src);
		Child& operator=(Child&& src);

	private:
		void operator~();

	};

	std::ostream& operator<<(std::ostream& os, const Child& src);



}


#endif // !SDDS_CHILD_H__
