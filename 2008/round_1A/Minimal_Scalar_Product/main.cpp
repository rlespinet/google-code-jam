#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

#define MAX_N 100

void do_test(int t) {
	
	int n;
	std::cin >> n;

	std::vector<int64_t> vec1(n);
	std::vector<int64_t> vec2(n);

	for (int i = 0; i < n; i++) {
		std::cin >> vec1[i];
	}

	for (int i = 0; i < n; i++) {
		std::cin >> vec2[i];
	}

	std::sort(vec1.begin(), vec1.end());
	std::sort(vec2.begin(), vec2.end());

	int64_t accum = 0;
	for (int i = 0; i < n; i++) {
		accum += vec1[i] * vec2[n - i - 1];
	}

	std::cout << "Case #" << t + 1 << ": " << accum << std::endl;
}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		do_test(i);
	}

	return 0;
}
