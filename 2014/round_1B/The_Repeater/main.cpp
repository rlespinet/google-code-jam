#include <iostream>
#include <string>
#include <algorithm>

#define MAX_N 100
#define MAX_L 100

std::string reduce(std::string &s) {
    std::string result;
    result.push_back(s[0]);
    for (int i = 1; i < s.length(); i++) {
	if (s[i] != s[i-1]) result.push_back(s[i]);
    }
    return result;
}

int count(std::string &s, int tab[]) {

    int tab_id = 0;
    tab[0] = 1;
    for (int i = 1; i < s.length(); i++) {
	if (s[i] == s[i-1]) {
	    tab[tab_id]++;
	} else {
	    tab_id++;
	    tab[tab_id] = 1;
	}
    }
    return tab_id+1;

}

void test(int t) {

    int N;
    std::cin >> N;
    std::string array[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> array[i];
    }

    bool possible = true;
    std::string reduced = reduce(array[0]);
    for (int i = 0; i < N; i++) {
	if (reduced != reduce(array[i])) {
	    possible = false;
	}
    }

    if (possible) {

	int min_count[MAX_L];
	for (int i = 0; i < reduced.length(); i++) {
	    min_count[i] = MAX_L;
	}

	int c[MAX_N][MAX_L];
	for (int i = 0; i < N; i++) {
	    count(array[i], c[i]);
	}

	int best_score[MAX_L];
	for (int i = 0; i < reduced.length(); i++) {

	    int min = MAX_L;
	    int max = 0;

	    for (int j = 0; j < N; j++) {
		min = std::min(min, c[j][i]);
		max = std::max(max, c[j][i]);
	    }

	    int best = MAX_L * MAX_N;
	    for (int k = min; k <= max; k++) {

		int cur_best = 0;
		for (int j = 0; j < N; j++) {
		    cur_best += std::abs(c[j][i] - k);
		}

		if (cur_best < best) {
		    best = cur_best;
		}
	    }

	    best_score[i] = best;

	}

	int result = std::accumulate(best_score, best_score + reduced.length(), 0);

	std::printf("Case #%d: %d\n", t + 1, result);

    } else {
	std::printf("Case #%d: Fegla Won\n", t + 1);
    }
}

int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

    return 0;
}
