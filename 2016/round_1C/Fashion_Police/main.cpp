#include <iostream>
#include <cstdint>
#include <cstring>

struct one_day {
	int j;
	int p;
	int s;
};

bool operator==(const one_day& x1, const one_day& x2) {
	return ((x1.j == x2.j) && (x1.p == x2.p) && (x1.s == x2.s));
}

#define MAX_S 10
#define MAX_K 10

#if 0

one_day possibilities[MAX_S * MAX_S * MAX_S];
int possibilities_size = 0;
int combination[3 * MAX_S * MAX_S];

one_day solution[MAX_S * MAX_S * MAX_S * MAX_K];
int solution_size;

void do_test_rec(int K, one_day *actual, int actual_size) {

	if (actual_size > solution_size) {
		solution_size = actual_size;
		for (int i = 0; i < actual_size; i++) {
			solution[i] = actual[i];
		}
	}

	for (int i = 0; i < possibilities_size; i++) {

		one_day possibility = possibilities[i];
		std::swap(possibilities[i], possibilities[--possibilities_size]);

		if (actual_size > 0 && actual[actual_size - 1] == possibility) {
			continue;
		}

		if (combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S] >= K ||
		    combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S] >= K ||
		    combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S] >= K) {
			continue;
		}

		combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S]++;
		combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S]++;
		combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S]++;

		actual[actual_size] = possibility;
		actual_size++;

		do_test_rec(K, actual, actual_size);

		actual_size--;

		combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S]--;
		combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S]--;
		combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S]--;

		std::swap(possibilities[i], possibilities[possibilities_size++]);
	}
	
}

void do_test(int n) {
	int J, P, S, K;
	std::cin >> J;
	std::cin >> P;
	std::cin >> S;
	std::cin >> K;

	possibilities_size = 0;

	for (int j = 0; j < J; j++) {
		for (int p = 0; p < P; p++) {
			for (int s = 0; s < S; s++) {
				possibilities[possibilities_size].j = j;
				possibilities[possibilities_size].p = p;
				possibilities[possibilities_size].s = s;
				possibilities_size++;
			}
		}
	}

	std::memset(combination, 0, sizeof(combination));
	solution_size = 0;

	one_day actual[MAX_S * MAX_S * MAX_S * MAX_K];
	int actual_size;

	do_test_rec(K, actual, actual_size);

	std::cout << "Case #" << n + 1 << ": " << solution_size << std::endl;
	for (int i = 0; i < solution_size; i++) {
		std::cout << solution[i].j + 1 << " "
			  << solution[i].p + 1 << " "
			  << solution[i].s + 1 << std::endl;
	}

}

#else

void do_test(int n) {
	int J, P, S, K;
	std::cin >> J;
	std::cin >> P;
	std::cin >> S;
	std::cin >> K;

	one_day possibilities[MAX_S * MAX_S * MAX_S];
	int possibilities_size = 0;
	int combination[3 * MAX_S * MAX_S] = {0};

	for (int j = 0; j < J; j++) {
		for (int p = 0; p < P; p++) {
			for (int s = 0; s < S; s++) {
				possibilities[possibilities_size].j = j;
				possibilities[possibilities_size].p = p;
				possibilities[possibilities_size].s = s;
				possibilities_size++;
			}
		}
	}

	for (int i = 0; i < possibilities_size; i++) {
		one_day possibility = possibilities[i];
		combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S]++;
		combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S]++;
		combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S]++;
	}

	for (;;) {

		int max_count = 0;
		int to_remove = 0;
		for (int i = 0; i < possibilities_size; i++) {
			one_day possibility = possibilities[i];

			int count = 0;

			if (combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S] > K) count++;
			if (combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S] > K) count++;
			if (combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S] > K) count++;
			if (count > max_count) {
				to_remove = i;
				max_count = count;
			}
		}

		if (max_count == 0) break;
	
		one_day possibility = possibilities[to_remove];

		combination[possibility.j + MAX_S * possibility.p + 0 * MAX_S * MAX_S]--;
		combination[possibility.p + MAX_S * possibility.s + 1 * MAX_S * MAX_S]--;
		combination[possibility.s + MAX_S * possibility.j + 2 * MAX_S * MAX_S]--;

		std::swap(possibilities[to_remove], possibilities[--possibilities_size]);

	}


	std::cout << "Case #" << n + 1 << ": " << possibilities_size << std::endl;
	for (int i = 0; i < possibilities_size; i++) {
		std::cout << possibilities[i].j + 1 << " "
			  << possibilities[i].p + 1 << " "
			  << possibilities[i].s + 1 << std::endl;
	}

}


#endif

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		do_test(i);
	}

	return 0;
}
