#include <iostream>
#include <cstdint>

#define MAX_B 50

#if 1

void do_test(int n) {

	int B;
	uint64_t M;
	std::cin >> B;
	std::cin >> M;

	if (M > (1UL << (B - 2))) {

		std::cout << "Case #" << n + 1 << ": IMPOSSIBLE\n";

	} else {

		int answer[MAX_B][MAX_B] = {0};
		for (int i = 1; i < B - 1; i++) {
			for (int j = B - 1; j > i; j--) {
				answer[i][j] = 1;
			}
		}

		if (M == (1UL << (B - 2))) {
			for (int i = 1; i < B; i++) {
				answer[0][i] = 1;
			}
		} else {

			for (int i = 0; i < B - 1; i++) {
				if (M & (1UL << static_cast<uint64_t>(i))) {
					answer[0][B - 2 - i] = 1;
				}
			}

		}

		std::cout << "Case #" << n + 1 << ": POSSIBLE\n";
		for (int i = 0; i < B; i++) {
			for (int j = 0; j < B; j++) {
				std::cout << answer[i][j];
			}
			std::cout << std::endl;
		}


	}

}

#else

void do_test(int n) {

	int initial_B;
	uint64_t M;
	std::cin >> initial_B;
	std::cin >> M;

	int answer[MAX_B][MAX_B] = {0};

	int B = initial_B;

	int to_link[3] = {B - 1, 0, 0};
	int to_link_size = 1;

	B--;

	while (B > 0 && M) {

		if (B == 4 || B == 2) {

			for (int i = 0; i < to_link_size; i++) {
				answer[B-2][to_link[i]] = 1;
				answer[B-1][to_link[i]] = 1;
			}

			to_link[0] = B - 2;
			to_link[1] = B - 1;
			to_link_size = 2;

			switch (M % 2) {
			case 1:
				answer[B-2][B-1] = 1;
			}

			M /= 2;
			B -= 2;

		} else {

			for (int i = 0; i < to_link_size; i++) {
				answer[B-3][to_link[i]] = 1;
				answer[B-2][to_link[i]] = 1;
				answer[B-1][to_link[i]] = 1;
			}


			to_link[0] = B - 3;
			to_link[1] = B - 2;
			to_link[2] = B - 1;
			to_link_size = 3;
		
			switch (M % 3) {
			case 2:
				answer[B-3][B-2];
			case 1:
				answer[B-3][B-1];
			}

			B -= 3;
			M /= 3;
		}

	}

	if (B <= 0 && M > 1) {
		std::cout << "Case #" << n + 1 << ": IMPOSSIBLE\n";
	} else {


		for (int i = 0; i < to_link_size; i++) {
			if (to_link[i] != 0) {
				answer[0][to_link[i]] = 1;
			}
		}

		std::cout << "Case #" << n + 1 << ": POSSIBLE\n";
		for (int i = 0; i < initial_B; i++) {
			for (int j = 0; j < initial_B; j++) {
				std::cout << answer[i][j];
			}
			std::cout << std::endl;
		}

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
