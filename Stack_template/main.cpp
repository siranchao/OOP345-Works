#include <iostream>
#include "Stack_module.h"

using namespace sdds;

int main() {
	Stack S;
	S.push(2);
	S.push(4);
	S.push(5);
	S.push(6);
	S.push(8);
	S.push(10);
	S.push(12);
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