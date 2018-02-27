#include <iostream>
#include <cstdint>

void do_test(int i) {
	uint64_t N;
	std::cin >> N;

	int digits[10] = {0};
	int num_digits = 0;

	std::cout << "Case #" << i + 1 << ": ";
	
	if (N == 0) {
		std::cout << "INSOMNIA" << std::endl;
	} else {
	
		for (int i = 1; ; i++) {

			uint64_t K = i * N;
			while (K) {
				int id = (K % 10);
				if (!digits[id]) {
					digits[id] = 1;
					if (num_digits == 9) {
						std::cout << i * N << std::endl;
						return;
					}
					num_digits++;

				}
				K /= 10;
			}

		}

	}

}

int main() {
	int T;
	std::cin >> T;
	for (int i = 0; i < T; i++) {
		do_test(i);
	}
}
