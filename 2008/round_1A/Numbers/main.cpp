#include <iostream>
#include <cmath>
#include <cstdint>

int64_t sqrt_int(int64_t i) {
	std::cout << i << std::endl;
#if 1
	return (int64_t) sqrt(i);
#else
	int64_t start = 0;
	int64_t end = i;

	while (end - start > 1) {
		int64_t mid = (start + end) / 2;
		if (mid * mid > i) {
			end = mid;
		} else if (mid * mid < i) {
			start = mid;
		} else {
			return mid;
		}
	}

	return start;
#endif
}

void do_test_rec(int n, int64_t &a, int64_t &b) {

	if (n == 1) {
		a = 1;
		b = 0;
		return;
	}

	do_test_rec(n / 2, a, b);
	int64_t old_a = a;
	int64_t old_b = b;
	a = (6 * old_a * old_a + 2 * old_a * old_b);
	b = (old_b * old_b - 4 * old_a * old_a);
	if (n & 0x1) {
		old_a = a;
		old_b = b;
		a = (6 * old_a + old_b);
		b = (- 4 * old_a);
	}
}

int do_test(int n) {

	int64_t a = 0;
	int64_t b = 0;
	do_test_rec(n, a, b);

	int64_t num = (3 * a + sqrt_int(a * a * 5) + b) % 1000;

	return num;
}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {

		int n;
		std::cin >> n;
		// std::cout << sqrt_int(n) << std::endl;
		std::cout << "Case #" << i + 1
			  << ": " << do_test(n)
			  << std::endl;
	}

	return 0;
}
