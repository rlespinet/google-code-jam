#include <iostream>
#include <fstream>
#include <cstdint>

#define MIN(_a, _b) (_a < _b ? _a : _b)

uint64_t reverse(uint64_t N) {
	uint64_t res = 0;
	while (N) {
		res *= 10;
		res += N % 10;
		N /= 10;
	}

	return res;
}

uint64_t naive_rec(uint64_t N, int64_t *tab) {

	if (tab[N] != -1) {
		return tab[N];
	}

	if (N < 10) {
		tab[N] = N;
		return N;
	}

	uint64_t c1 = naive_rec(N-1, tab);

	uint64_t revN = reverse(N);

	if (revN >= N || N % 10 == 0) {
		tab[N] = c1 + 1;
		return c1 + 1;
	}

	uint64_t c2 = naive_rec(reverse(N), tab);

	if (c1 < c2) {
		tab[N] = c1 + 1;
		return 1 + c1;
	} else {
		tab[N] = c2 + 1;
		return 1 + c2;
	}


}

uint64_t solve(uint64_t N) {

	uint64_t copyN = N;
	uint64_t sizeN = 0;
	uint64_t tabN[15] = {0};
	uint64_t res;

	while (copyN) {
		tabN[sizeN] = copyN % 10;
		copyN /= 10;
		sizeN++;
	}

	if (sizeN <= 1) {
		res = N;
		return res;
	}

	uint64_t mid = (sizeN + 1) / 2;
	uint64_t count = 0;
	for (int64_t i = mid - 1; i >= 0; i--) {
		count *= 10;
		count += tabN[i];
	}


	if (count == 0) {
		res = 1 + solve(N - 1);
		return res;
	}

	uint64_t newN = N - count + 1;

	if (reverse(newN) >= newN) {
		res = count + 1 + solve(newN - 2);
		return res;
	} else {
		res = count + solve(reverse(newN));
		return res;
	}

}

void usage() {
	std::cout << "Usage : ./counter_culture <input_file>";
	std::cout << std::endl;
	exit(-1);
}

int main(int argc, char** argv) {

	if (argc != 2) {
		usage();
	}

	int test_count;
	std::ifstream input(argv[1]);

	input >> test_count;

	for (int i = 0; i < test_count; i++) {
		uint64_t N;
		input >> N;
		uint64_t solution = solve(N);
		std::cout << "Case #";
		std::cout << i + 1;
		std::cout << ": ";
		std::cout << solution;
		std::cout << std::endl;
	}

}
