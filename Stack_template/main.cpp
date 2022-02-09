#include <iostream>
//#include "Stack_module.h"
#include "Stack_template.h"

using namespace sdds;

int main() {
	//using double
	Stack<double> S;
	S.push(5.12);
	S.push(6.12);
	S.push(8.66);
	S.push(10.9);
	S.push(12.15);
	S.push(32.15);
	//Pop out 3 nodes
	for (size_t  i = 0; i < 3; i++) {
		std::cout << S.pop() << " | current depth: " << S.depth() - 1 << std::endl;
	}
	if (S) {
		std::cout << "Stack is not empty" << std::endl;
	}
	else {
		std::cout << "Stack is empty" << std::endl;
	}
	std::cout << "nodes left: " << S.depth() << std::endl;


	//using string
	Stack<std::string> E;
	E.push("HELLO line 1");
	E.push("HELLO LINE 2");
	E.push("HELLO LINE 3");
	E.push("HELLO LINE 4");
	E.push("HELLO LINE 5");
	E.push("HELLO LINE 6");
	//Pop out 3 nodes
	for (size_t i = 0; i < 3; i++) {
		std::cout << E.pop() << " | current depth: " << E.depth() - 1 << std::endl;
	}
	if (E) {
		std::cout << "Stack is not empty" << std::endl;
	}
	else {
		std::cout << "Stack is empty" << std::endl;
	}
	std::cout << "nodes left: " << E.depth() << std::endl;

	//test rule of five
	Stack<double> B;
	B.push(123.12);
	B.push(126.12);
	B.push(228.66);
	B.push(1210.9);
	S = B;
	for (size_t i = 0; i < 2; i++) {
		std::cout << S.pop() << " | current depth: " << S.depth() - 1 << std::endl;
	}
	std::cout << "original nodes left: " << B.depth() << std::endl;


	Stack<std::string> F;
	F.push("ByeBye Line 1");
	F.push("ByeBye LINE 2");
	F.push("ByeBye LINE 3");
	F.push("ByeBye LINE 4");
	E = std::move(F);
	for (size_t i = 0; i < 2; i++) {
		std::cout << E.pop() << " | current depth: " << E.depth() - 1 << std::endl;
	}
	std::cout << "original nodes left: " << F.depth() << std::endl;




	return 0;
}