#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_POW_N 20

bool is_tidy(std::string &s) {

    for (int i = 0; i < s.size() - 1; i++) {
	if (s[i] > s[i+1]) {
	    return false;
	}
    }

    return true;

}


void print_tidy(std::string &s) {

    int i = 0;
    while (s[i] == '0') i++;

    while (i < s.length()) {
	std::cout << s[i++];
    }

}

void test(int t) {

    std::string s;
    std::cin >> s;

    int id = s.length() - 1;
    while (!is_tidy(s)) {
	int k = id - 1;
	while (s[k] == '0') {
	    s[k] = '9';
	    k--;
	}
	s[k]--;
	s[id--] = '9';
    }

    std::cout << "Case #" << t + 1 << ": ";

    print_tidy(s);

    std::cout << std::endl;

}

int main(int argc, char **argv) {

    // std::cout << is_tidy(8) << std::endl;
    // std::cout << is_tidy(123) << std::endl;
    // std::cout << is_tidy(555) << std::endl;
    // std::cout << is_tidy(224488) << std::endl;

    // std::cout << is_tidy(20) << std::endl;
    // std::cout << is_tidy(321) << std::endl;
    // std::cout << is_tidy(495) << std::endl;
    // std::cout << is_tidy(99990) << std::endl;


    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++) {
    	test(t);
    }


    return 0;
}
