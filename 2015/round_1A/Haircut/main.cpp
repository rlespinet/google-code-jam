#include <iostream>
#include <vector>
#include <cstdint>

#include "barber_list.hpp"

#define MIN(_a, _b) ((_a < _b) ? _a : _b)
#define MAX(_a, _b) ((_a > _b) ? _a : _b)

uint64_t gcd(uint64_t a, uint64_t b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

uint64_t lcm(uint64_t a, uint64_t b) {
	uint64_t d = gcd(a,b);
	return a / d * b;
}


inline uint64_t eval(uint64_t t, const std::vector<uint64_t>& data) {

	uint64_t N = 0;
	for (uint64_t i = 0; i < data.size(); i++) {
		N += t / data[i] + 1;
	}

	return N;
}

// inline uint64_t accu(uint64_t t, uint64_t N, const std::vector<uint64_t>&data) {

// 	const int Nt = eval(t, data);

// 	std::vector<uint64_t> acc(data.size());

// 	for (uint64_t i = 0; i < acc.size(); i++) {
// 		acc[i] = (t / data[i]) * data[i];
// 	}

// 	for (uint64_t n = Nt; n < N; n++) {

// 	}

// }

inline uint64_t min_left(uint64_t t, uint64_t N, const std::vector<uint64_t>&data) {

	uint64_t diff = N - eval(t, data);
	uint64_t id = 0;

	for (uint64_t i = 0; i < data.size(); i++) {

		const uint64_t elt = ((t / data[i]) + 1) * data[i];

		if (elt == t+1 && --diff == 0) {
			id = i;
			break;
		}
	}

	return id;
}

uint64_t solution() {

	uint64_t B, N;
	std::cin >> B;
	std::cin >> N;

	std::vector<uint64_t> data(B);
	for (uint64_t i = 0; i < B; i++) {
		uint64_t element;
		std::cin >> element;
		data[i] = element;
	}

	uint64_t min = data[0];
	uint64_t max = data[0];

	for (uint64_t i = 0; i < data.size(); i++) {
		min = MIN(data[i], min);
		max = MAX(data[i], max);
	}

	uint64_t tmin = (N - B) / B * min - 1;
	uint64_t tmax = N * max / B + B;
	uint64_t t;

	for (;;) {

		t = (tmax + tmin) / 2;

		const uint64_t Nt = eval(t, data);

		if (tmax - tmin <= 1)
			break;

		if (Nt < N)
			tmin = t;
		else
			tmax = t;
	}

	return min_left(tmin, N, data) + 1;

}

int main(int argc, char** argv) {

	uint64_t test_count;
        std::cin >> test_count;

	for (uint64_t i = 0; i < test_count; i++) {
		std::cout << "Case #";
		std::cout << i + 1;
		std::cout << ": ";
		std::cout << solution();
		std::cout << std::endl;
	}


}
