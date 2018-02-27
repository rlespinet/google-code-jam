#include <iostream>
#include <cstdio>

#define MAX_S 1000

void do_test(int n) {

	std::string  S;
	std::cin >> S;
	
	char data[MAX_S * 2];
	
	char *start = data + MAX_S;
	char *end = data + MAX_S + 1;

	*start = S[0];

	for (int i = 1; i < S.length(); i++) {
		if (S[i] >= *start) {
			start--;
			*start = S[i];
		} else {
			*end = S[i];
			end++;
		}
	}

	*end = 0;
	printf("Case #%d: %s\n", n + 1, start);
	

}

int main() {

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		do_test(i);
	}

	return 0;
}
