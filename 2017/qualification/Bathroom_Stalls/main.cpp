#include <iostream>
#include <algorithm>
#include <cstdint>

#define MAX_N 1000

int64_t min;
int64_t max;

void test_rec(int64_t N, int64_t K) {

    if (K == 1) {
	min = (N - 1) / 2;
	max = N / 2;
    } else {
	K--;
	if (K & 1) {
	    test_rec(N / 2, (K + 1) / 2);
	} else {
	    test_rec((N - 1) / 2, K / 2);
	}
    }
}

void test(int64_t t) {

    int64_t N, K;
    std::cin >> N;
    std::cin >> K;

    test_rec(N, K);

    std::cout << "Case #" << t + 1 << ": ";

    std::cout << max << " " << min;

    std::cout << std::endl;

}

int main(int argc, char **argv) {

    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++) {
	test(t);
    }


    return 0;
}
