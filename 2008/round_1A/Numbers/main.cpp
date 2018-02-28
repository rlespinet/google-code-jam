#include <iostream>
#include <cmath>
#include <cstdint>

int do_test(int n) {

    uint64_t a = 1;
    uint64_t b = 0;

    for (int i = 63; i >= 0; i--) {

        uint64_t na = a * a + 5 * b * b;
        uint64_t nb = 2 * a * b;
        a = na;
        b = nb;

        if ((1L << i) & n) {
            uint64_t na = 3 * a + 5 * b;
            uint64_t nb = 3 * b + a;
            a = na;
            b = nb;
        }

        a %= 1000;
        b %= 1000;

    }

    return (2 * a - 1) % 1000;
}

void print_padded_1000(uint64_t n) {

    uint64_t c = 3;
    for (uint64_t p = 1; c > 0 && n > p; p *=10, c--);

    while (c--) {
        std::cout << '0';
    }

    std::cout << n;
}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {

		int n;
		std::cin >> n;
		std::cout << "Case #" << i + 1 << ": ";
                print_padded_1000(do_test(n));
                std::cout << std::endl;
	}

	return 0;
}
