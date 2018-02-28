#include <iostream>
#include <exception>
#include <stdexcept>

#include "line.hpp"

#define MAX(_a, _b) ((_a > _b)?_a:_b)

template<class T>
T process1(line<T> line) {

	const int size = line.size();

	if (size <= 1) {
		throw std::invalid_argument("Need more than one value");
	}

	T res = 0;
	for (int i = 0; i < size - 1; i++) {
		if (line[i+1] < line[i]) {
			res += line[i] - line[i+1];
		}
	}

	return res;

}

template<class T>
T process2(line<T> line) {
	const int size = line.size();

	if (size <= 1) {
		throw std::invalid_argument("Need more than one value");
	}

	T max = 0;
	for (int i = 0; i < size - 1; i++) {
		max = MAX(max, line[i] - line[i+1]);
	}

	int compensate = 0;
	for (int i = 0; i < size - 1; i++) {
		const int op = line[i] - max;
		if (op < 0) {
			compensate += op;
		}
	}

	int res = (size - 1) * max + compensate;

	return res;
}



template<class T>
void dump(const line<T>& line) {
	for (auto it = line.begin(); it != line.end(); it++) {
		std::cout << *it;
		std::cout << " ";
	}
	std::cout << std::endl;
}


void process_test() {
	int data_number;
	std::cin >> data_number;

	if (data_number <= 0) {
		throw std::invalid_argument("Wrong line in input file");
	}

	line<int> line(data_number);
	for (int i = 0; i < data_number; i++) {
		int data;
		std::cin >> data;
		line[i] = data;
	}

	std::cout << process1<int>(line);
	std::cout << " ";
	std::cout << process2<int>(line);
}


int main(int argc, char **argv) {

	int test_number;
        std::cin >> test_number;

	for (int i = 0; i < test_number; i++) {
		std::cout << "Case #";
		std::cout << i + 1;
		std::cout << ": ";
		process_test();
		std::cout << std::endl;
	}

	return 0;
}
