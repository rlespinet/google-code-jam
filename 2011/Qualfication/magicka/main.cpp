#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <vector>

#define HASH(_c1, _c2) (((_c1) - 'A') * 26 + ((_c2) - 'A'))

void test(int t) {

    std::map<int, char> repl;

    int C;
    std::cin >> C;
    for (int i = 0; i < C; i++) {
	std::string s;
	std::cin >> s;
	repl[HASH(s[0], s[1])] = s[2];
	repl[HASH(s[1], s[0])] = s[2];
    }

    std::map<char, std::vector<char>> clear;

    int D;
    std::cin >> D;
    for (int i = 0; i < D; i++) {
	std::string s;
	std::cin >> s;
	clear[s[0]].push_back(s[1]);
	clear[s[1]].push_back(s[0]);
    }

    int N;
    std::cin >> N;
    std::string s;
    std::cin >> s;

    char occ[26] = {};
    std::string final_str;
    for (int i = 0; i < N; i++) {

	final_str.push_back(s[i]);
	occ[s[i] - 'A']++;
	while (final_str.length() > 1) {
	    auto it = repl.find(HASH(final_str[final_str.length() - 1],
				     final_str[final_str.length() - 2]));
	    if (it != repl.end()) {
		occ[final_str.back() - 'A']--;
		final_str.pop_back();
		occ[final_str.back() - 'A']--;
		final_str.pop_back();
		final_str.push_back(it->second);
		occ[it->second - 'A']++;
	    } else {
		break;
	    }

	}

	auto it = clear.find(final_str.back());
	if (it != clear.end()) {
	    for (int j = 0; j < it->second.size(); j++) {
		if (occ[it->second[j] - 'A']) {
		    final_str.clear();
		    std::memset(occ, 0, sizeof(char) * 26);
		    break;
		}
	    }
	}
	// for (int i = 0; i < 26; i++) {
	//     std::cout << ((char) ('A' + i)) << ": " << (int) occ[i] << std::endl;
	// }

    }

    std::printf("Case #%d: ", t + 1);
    if (final_str.empty()) {
	std::printf("[]\n");
    } else {
	std::printf("[%c", final_str[0]);
	for (int i = 1; i < final_str.length(); i++) {
	    std::printf(", %c", final_str[i]);
	}
	std::printf("]\n");
    }

}

int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

}
