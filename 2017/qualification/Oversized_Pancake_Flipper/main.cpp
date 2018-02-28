#include <iostream>
#include <algorithm>
#include <string>

void test(int t) {

    std::string s;
    std::cin >> s;

    int K;
    std::cin >> K;


    int count = 0;
    for (int i = 0; i < s.length() - K + 1; i++) {
	if (s[i] == '-') {
	    for (int k = 0; k < K; k++) {
		s[i+k] = (s[i+k] == '-' ? '+' : '-');
	    }
	    count++;
	}
    }

    std::cout << "Case #" << t + 1 << ": ";
    if (std::all_of(s.begin(), s.end(), [](char &c) { return c == '+'; })) {
	std::cout << count;
    } else {
	std::cout << "IMPOSSIBLE";
    }

    std::cout << std::endl;

}

int main(int argc, char **argv) {

    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++) {
	test(t);
    }


    return 0;
}
