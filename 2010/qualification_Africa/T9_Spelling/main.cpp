#include <iostream>

#define MAX_L 1000

int num_map[256];

void init() {
	num_map[(int) 'a'] = 2;
	num_map[(int) 'b'] = 22;
	num_map[(int) 'c'] = 222;

	num_map[(int) 'd'] = 3;
	num_map[(int) 'e'] = 33;
	num_map[(int) 'f'] = 333;

	num_map[(int) 'g'] = 4;
	num_map[(int) 'h'] = 44;
	num_map[(int) 'i'] = 444;

	num_map[(int) 'j'] = 5;
	num_map[(int) 'k'] = 55;
	num_map[(int) 'l'] = 555;

	num_map[(int) 'm'] = 6;
	num_map[(int) 'n'] = 66;
	num_map[(int) 'o'] = 666;

	num_map[(int) 'p'] = 7;
	num_map[(int) 'q'] = 77;
	num_map[(int) 'r'] = 777;
	num_map[(int) 's'] = 7777;

	num_map[(int) 't'] = 8;
	num_map[(int) 'u'] = 88;
	num_map[(int) 'v'] = 888;

	num_map[(int) 'w'] = 9;
	num_map[(int) 'x'] = 99;
	num_map[(int) 'y'] = 999;
	num_map[(int) 'z'] = 9999;

	num_map[(int) ' '] = 0;
}

void do_test(int n) {

	char buffer[MAX_L + 1];
	std::cin.getline(buffer, MAX_L);

	std::cout << "Case #" << n + 1 << ": ";

	int i = 0;
	int prc_num = 1;
	while (buffer[i]) {
		int num = num_map[buffer[i]];
		if ((num % 10) == (prc_num % 10)) {
			std::cout << ' ';
		}
		std::cout << num;
		prc_num = num;
		i++;
	}

	std::cout << std::endl;
}

int main() {

	int N;
	std::cin >> N;
	std::cin.ignore(0xFFFFFFFF, '\n');

	init();

	for (int n = 0; n < N; n++) {
		do_test(n);
	}

	return 0;
}
