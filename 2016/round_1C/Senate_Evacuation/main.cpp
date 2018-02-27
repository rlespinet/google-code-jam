#include <iostream>

#define MAX_N 26

void do_test(int n) {

	int N;
	std::cin >> N;

	int count[MAX_N];
	// char match[MAX_N] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int total = 0;
	
	for (int i = 0; i < N; i++) {
		std::cin >> count[i];
		total += count[i];
	}

	while (total > 0) {
		
		int id_max1 = 0;
		int id_max2 = 0;

		for (int i = 1; i < N; i++) {
			if (count[id_max1] <= count[i]) {
				id_max2 = id_max1;
				id_max1 = i;
			}

			if (count[id_max2] <= count[i] && 
			    count[id_max2] < count[id_max1]) {
				id_max2 = i;
			}
		}

		std::cout << ' ';
		if (total == 1) {
			std::cout << (char) (id_max1 + 'A');
			total -= 1;
		} else if (count[id_max2] <= (total - 2) / 2) {
			count[id_max1] -= 2;
			std::cout << (char) (id_max1 + 'A');
			std::cout << (char) (id_max1 + 'A');
			total -= 2;
		} else if (count[id_max1] - 1 <= (total - 2) / 2 &&
			   count[id_max2] - 1 <= (total - 2) / 2) {
			count[id_max1] -= 1;
			count[id_max2] -= 1;
			std::cout << (char) (id_max1 + 'A');
			std::cout << (char) (id_max2 + 'A');
			total -= 2;
		} else if (count[id_max2] - 1 <= (total - 1) / 2) {
			std::cout << (char) (id_max2 + 'A');
			count[id_max2]--;
			total--;
		} else if (count[id_max1] - 1 <= (total - 1) / 2) {
			std::cout << (char) (id_max1 + 'A');
			count[id_max1]--;
			total--;
		} else {
			std::cout << "ERROR";
			return;
		}


	}

	std::cout << std::endl;
	
}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		do_test(i);
	}

	return 0;
}
