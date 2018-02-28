#include <iostream>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MAX_C 1000
#define MAX_P 1000
#define MAX_I 2000

void do_test(int n) {
	int C, I;
	std::cin >> C;
	std::cin >> I;

	int price_obj[MAX_P] = {0};

	int snd_half = 0;

	for (int i = 0; i < I; i++) {
		int P;
		std::cin >> P;
		if (2 * P == C && price_obj[P]) {
			snd_half = i + 1;
		} else {
			price_obj[P] = i + 1;
		}

	}

	if (snd_half) {
		std::cout << "Case #" << n + 1 << ": ";
		std::cout << price_obj[C / 2];
		std::cout << " ";
		std::cout << snd_half;
		std::cout << std::endl;
		return;
	}

	for (int i = 0; i < C / 2; i++) {
		if (price_obj[i] != 0 &&
		    price_obj[C - i] != 0) {

			int first = MIN(price_obj[i], price_obj[C - i]);
			int second = MAX(price_obj[i], price_obj[C - i]);

			std::cout << "Case #" << n + 1 << ": ";
			std::cout << first;
			std::cout << " ";
			std::cout << second;
			std::cout << std::endl;
			return;
		}
	}

	std::cout << "Case #" << n + 1 << ": ? ?\n";
}

int main() {
	
	int N;
	std::cin >> N;

	for (int n = 0; n < N; n++) {
		do_test(n);
	}

	return 0;
}
