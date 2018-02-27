#include <iostream>
#include <cstdint>
#include <cmath>

#define N 500
#define J 32

void verify(int n) {
	
	char jam[J + 1] = {0};

	std::cin.read(jam, J);

	std::cout << "--------------------" << std::endl;
	std::cout << jam << std::endl;

	for (int i = 2; i <= 10; i++) {

		uint64_t num = 0;
		for (int j = 0; j < J; j++) {
			num += (jam[j] == '1') ? std::pow(i, J - 1 - j) : 0;
		}

		int div;
		std::cin >> div;

		std::cout << div;
		std::cout << " ";
		std::cout << num;
		std::cout << " ";
		std::cout << ((num % div) ? "KO" : "OK");
		std::cout << std::endl;

	}
	std::cin.ignore(0xFFFFFFFF, '\n');

}

int main() {
	std::cin.ignore(0xFFFFFFFF, '\n');

	for (int i = 0; i < N; i++) {
		verify(i);
	}
	
	return 0;
}
