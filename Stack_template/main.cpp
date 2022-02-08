#include <iostream>
//#include "Stack_module.h"
#include "Stack_template.h"

using namespace sdds;

int main() {
	Stack<double> S;
	S.push(5.12);
	S.push(6.12);
	S.push(8.66);
	S.push(10.9);
	S.push(12.15);
	for (int i = 0; i < 4; i++) {
		std::cout << S.pop() << std::endl;
	}

	if (S) {
		std::cout << "Stack is not empty" << std::endl;
	}
	if (S.isEmpty()) {
		std::cout << "Stack is empty" << std::endl;
	}


	return 0;
}