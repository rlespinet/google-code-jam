#include <iostream>
#include <cstdint>
#include <cmath>

#define MAX_T 100
#define MAX_K 100
#define MAX_C 100

// 10 ^ 18 -> 1000^6

void do_test_easy(int t) {
	int K, C, S;
	std::cin >> K >> C >> S;

	std::cout << "Case #" << t + 1 << ": ";
	
	if (S < K) {
		std::cout << "IMPOSSIBLE" << std::endl;
		return;
	}

	uint64_t result[MAX_K];

	// sum K ^ 2 * k + K * k + k
	for (int k = 0; k < K; k++) {
		uint64_t num = 0;
		for (int i = 0; i < C; i++) {
			num = num * static_cast<int64_t>(K) + static_cast<int64_t>(k);
		}
		result[k] = num + 1;
	}

	
	std::cout << result[0];
	for (int k = 1; k < K; k++) {
		std::cout << " " << result[k];
	}

	std::cout << std::endl;

}

void do_test_hard(int t) {
	int K, C, S;
	std::cin >> K >> C >> S;

	std::cout << "Case #" << t + 1 << ": ";

	if (S * C < K) {
		std::cout << "IMPOSSIBLE" << std::endl;
		return;
	}

	int result_size = 0;
	int64_t result[MAX_K];
	int M = 0;
	while (M < K) {
		int64_t num = 0;
		for (int i = 0; i < C; i++) {
			num *= static_cast<int64_t>(K);
			if (M < K) {
				num += static_cast<int64_t>(M);
			}
			M++;
		}
		result[result_size++] = num;
	}

	std::cout << result[0] + 1;
	for (int k = 1; k < result_size; k++) {
		std::cout << " " << result[k] + 1;
	}
	std::cout << std::endl;

}

int main() {
	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++) {
		do_test_hard(t);
	}

	return 0;
}
