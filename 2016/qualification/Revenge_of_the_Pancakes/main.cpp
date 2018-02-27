#include <iostream>

#define MAX_S 128

int do_test(int n) {
	char buffer[MAX_S + 2];
	std::cin.getline(buffer, MAX_S);

	int length = 0;
	while (buffer[length]) length++;
	
	if (length == 0) return 0;

	int num_chg = 0;
	char last = buffer[0];
	buffer[length] = '+';

	for (int i = 0; i < length + 1; i++) {
		
		if (buffer[i] != last) {
			last = buffer[i];
			num_chg++;
		}
	}

	return num_chg;

}

int main() {
	int N;
	std::cin >> N;
	std::cin.ignore(0xFFFFFFFF, '\n');
	for (int n = 0; n < N; n++) {
		std::cout << "Case #" << n + 1 << ": ";
		std::cout << do_test(n) << std::endl;
	}
	
	return 0;
}
