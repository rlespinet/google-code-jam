#include <iostream>
#include <cstring>

#define MAX_S 2000

void do_test(int n) {

	std::string buffer;
	std::cin >> buffer;
	
	int S = buffer.length();

	int count[26] = {};
	for (int i = 0; i < S; i++) {
		count[buffer[i] - 'A']++;
	}

	char array[][10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
	int array_size = 10;

	int processed[10] = {};
	int processed_number = 0;

	int final[10] = {};

	while (processed_number < 10) {

		int letter_map[26] = {};

		for (int i = 0; i < 10; i++) {
			if (processed[i]) continue;

			for (int j = 0; j < std::strlen(array[i]); j++) {
				if (letter_map[array[i][j] - 'A']) {
					letter_map[array[i][j] - 'A'] = 0xFF;
				} else {
					letter_map[array[i][j] - 'A'] = i + 1;
				}
			}
		}

		for (int i = 0; i < 26; i++) {
			if (letter_map[i] && letter_map[i] != 0xFF) {

				int k = letter_map[i] - 1;
				if (!processed[k]) {
					int c = count[i];
					final[k] = c;

					for (int j = 0; j < std::strlen(array[k]); j++) {
						count[array[k][j] - 'A'] -= c;
					}

					processed[k] = 1;
					processed_number++;
				}

			}
		}

	}

	std::cout << "Case #" << n + 1 << ": ";
	for (int i = 0; i < 10; i++) {
		while (final[i]) {
			std::cout << i;
			final[i]--;
		}
	}
	std::cout << std::endl;
}

void test() {
	
	char str[] = "ZEROONETWOTHREEFOURFIVESIXSEVENEIGHTNINE";

	int count[26] = {};

	for (int i = 0; i < sizeof(str); i++) {
		count[str[i] - 'A']++;
	}

	for (int i = 0; i < 26; i++) {
		std::cout << (char) ('A' + i) << " : " << count[i] << std::endl;
	}

}

int main() {

	// test();
	// return 0;

	int T;
	std::cin >> T;

	for (int n = 0; n < T; n++) {
		do_test(n);
	}

	return 0;
}
