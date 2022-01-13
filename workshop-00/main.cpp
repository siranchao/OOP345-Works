/*
Name: Siran Cao
email: scao34@myseneca.ca
ID: 159235209
Date: 01/13/2022
Description: Swap and bubble sorting functions
*/
#include <iostream>

namespace sdds {
	//swap ints
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	//bubble sorting
	void sort(int* list, int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int k = 0; k < n - i - 1; k++) {
				if (list[k] > list[k + 1]) {
					swap(list[k], list[k + 1]);
				}
			}
		}
	}

}

using namespace sdds;
using namespace std;

int main() {
	const int size = 10;
	int arr[size] = { 2, 3, 90, 23, 34, 78, 12, 22, 8, 55 };
	sort(arr, size);
	for (int i = 0; i < size; i++) {
		cout << arr[i] << endl;
	}

	return 0;
}