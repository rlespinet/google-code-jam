#include <iostream>
#include <cstdio>

#define MAX_N 50
#define MAX_HEIGHT 2500

void do_test(int t) {

	int N;
	std::cin >> N;

	int count[MAX_HEIGHT + 1] = {};
	int count_size = 0;

	for (int i = 0; i < 2 * N - 1; i++) {

		for (int j = 0; j < N; j++) {
			int num;
			std::cin >> num;
			count[num]++;
			count_size = (count_size > num) ? count_size : num;
		}

	}

	printf("Case #%d:", t + 1);
	for (int i = 0; i <= count_size; i++) {
		if (count[i] & 0x1)
			printf(" %d", i);
	}
	printf("\n");

}

int main() {

	int T;
	std::cin >> T;
	
	for (int t = 0; t < T; t++) {
		do_test(t);
		fprintf(stderr, "DONE : %d/%d\n", t + 1, T);
	}

}
