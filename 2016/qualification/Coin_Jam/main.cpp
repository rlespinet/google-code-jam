#include <iostream>
#include <cstdint>
#include <cstring>

#define N 32
#define J 500

uint8_t refjam[] = {1, 0, 0, 1};
uint32_t refnum[] = {3, 2, 5, 2, 3, 2, 3, 2, 7};
const char *refstr = "3 7 5 6 31 8 27 5 77";

// 1001
// 9
// 28
// 65
// 126
// 217
// 344
// 513
// 730
// 1001

bool can_place(uint8_t *jam, int id) {
	for (int i = 0; i < sizeof(refjam); i++) {
		if (jam[id + i] & refjam[i]) return false;
	}

	return true;
}

void recursive_find(uint8_t pjam[], int id, int &left) {

	if (left == 0) return;

	uint8_t jam[N];
	std::memcpy(jam, pjam, N);

	for (int i = id; i < (N - sizeof(refjam)); i++) {
		if (can_place(jam, i)) {
			for (int j = 0; j < sizeof(refjam); j++) {
				jam[i + j] += refjam[j];
			}

			char buffer[N + 1];
			for (int j = 0; j < N; j++) {
				buffer[j] = jam[N - 1 - j] + '0';
			}
			buffer[N] = 0;
			std::cout << buffer << " " << refstr << std::endl;

			left--;
			recursive_find(jam, i + 1, left);
			if (left == 0) return;

			for (int j = 0; j < sizeof(refjam); j++) {
				jam[i + j] -= refjam[j];
			}
			
		}
	}

}

int main() {
	
	uint8_t jam[N] = {0};

	std::memcpy(jam, refjam, sizeof(refjam));

	std::memcpy(jam + N - sizeof(refjam), refjam, sizeof(refjam));

	std::cout << "Case #1:" << std::endl;

	int left = J;
	recursive_find(jam, 0, left);

	return 0;
}
