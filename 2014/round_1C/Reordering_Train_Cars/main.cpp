#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <algorithm>

#define MAX_N 100

#define MOD_ASKED 1000000007

int count;

bool is_valid(std::string *s, int N) {

    int map[256];
    for (int i = 0; i < 256; i++) {
	map[i] = -1;
    }

    std::string f;
    for (int i = 0; i < N; i++) {
	f.append(s[i]);
    }

    for (int i = 0; i < f.length(); i++) {
	if (map[f[i]] != -1 && i - map[f[i]] > 1) {
	    return false;
	} else {
	    map[f[i]] = i;
	}
    }

    return true;

}

bool is_valid(std::string s) {

    int map[256];
    for (int i = 0; i < 256; i++) {
	map[i] = -1;
    }

    for (int i = 0; i < s.length(); i++) {
	if (map[s[i]] != -1 && i - map[s[i]] > 1) {
	    return false;
	} else {
	    map[s[i]] = i;
	}
    }

    return true;

}


void test_rec(std::string *s, int i, int N) {

    if (i >= N) {
	if (is_valid(s, N)) {
	    count++;
	}
    }

    for (int j = i; j < N; j++) {
	std::swap(s[i], s[j]);
	test_rec(s, i + 1, N);
	std::swap(s[i], s[j]);
    }

}


void test_naive(int t) {
    int N;
    std::cin >> N;

    std::string s[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> s[i];
    }

    count = 0;
    test_rec(s, 0, N);

    std::printf("Case #%d: %d\n", t + 1, count);

}

int64_t factModed[MAX_N + 1];

void test(int t) {
    int N;
    std::cin >> N;

    std::string s[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> s[i];
    }

    int same[256] = {};
    std::vector<std::string> not_same;

    for (int i = 0; i < N; i++) {
	if (std::all_of(s[i].begin(), s[i].end(), [=](char c) {return c == s[i][0];})) {
	    same[s[i][0]]++;
	} else {
	    not_same.push_back(s[i]);
	}
    }

    int64_t count = 1;
    bool char_map[256] = {};

    std::string f;
    if (!not_same.empty()) {
	f = not_same.back();
	not_same.pop_back();
	while (!not_same.empty()) {

	    bool found = false;
	    for (int i = 0; i < not_same.size(); i++) {
		if (not_same[i].front() == f.back()) {
		    for (int j = 1; j < not_same[i].length(); j++) {
			if (char_map[not_same[i][j]]) {
			    count = 0;
			    goto end;
			}
		    }
		    for (int j = 0; j < not_same[i].length(); j++) {
			char_map[not_same[i][j]] = true;
		    }
		    f = f + not_same[i];
		    std::swap(not_same[i], not_same.back());
		    not_same.pop_back();
		    found = true;
		    break;
		} else if (not_same[i].back() == f.front()) {
		    for (int j = 0; j < not_same[i].length() - 1; j++) {
			if (char_map[not_same[i][j]]) {
			    count = 0;
			    goto end;
			}
		    }
		    for (int j = 0; j < not_same[i].length(); j++) {
			char_map[not_same[i][j]] = true;
		    }
		    f = not_same[i] + f;
		    std::swap(not_same[i], not_same.back());
		    not_same.pop_back();
		    found = true;
		    break;
		}
	    }

	    if (!found) {
		f += not_same.back();
		not_same.pop_back();
		count =  (count * 2) % 1000000007;
	    }

	    if (same[f.front()]) {
		count = (count * factModed[same[f.front()]]) % 1000000007;
		same[f.front()] = 0;
	    }

	    if (same[f.back()]) {
		count = (count * factModed[same[f.back()]]) % 1000000007;
		same[f.back()] = 0;
	    }

	}
    }
end:
    for (int c = 'a'; c <= 'z'; c++) {
	if (same[c]) {
	    if (char_map[c]) {
		count = 0;
		break;
	    } else {
		count = (count * factModed[same[f.back()]]) % 1000000007;
	    }
	}
    }

    std::printf("Case #%d: %ld\n", t + 1, count);

}


void test2(int t) {

    int N;
    std::cin >> N;

    std::string s[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> s[i];
    }

    int blocs = N;
    std::vector<int64_t> counter;

    std::vector<std::string> not_same;

    int same[256] = {};
    bool valid_same[256] = {};

    for (int i = 0; i < N; i++) {
	if (std::all_of(s[i].begin(), s[i].end(), [=](char c) {return c == s[i][0];})) {
	    same[s[i][0]]++;
	} else {
	    not_same.push_back(s[i]);
	    counter.push_back(1);
	}
    }

    bool run = true;
    while (run) {
	run = false;
	for (int i = 0; i < not_same.size(); i++) {
	    for (int j = 0; j < not_same.size(); j++) {
		if (i == j) continue;
		if (not_same[i].front() == not_same[j].back()) {
		    if (same[not_same[i].front()]) valid_same[not_same[i].front()] = true;
		    not_same[j] += not_same[i];
		    counter[j] = (counter[j] * counter[i]) % MOD_ASKED;
		    std::swap(not_same[i], not_same.back());
		    std::swap(counter[i], counter.back());
		    not_same.pop_back();
		    counter.pop_back();
		    run = true;
		    break;
		}
	    }
	}
    }

    for (int i = 0; i < not_same.size(); i++) {
	if (same[not_same[i].front()]) {
	    counter[i] = (counter[i] * factModed[same[not_same[i].front()]]) % MOD_ASKED;
	    same[not_same[i].front()] = 0;
	}
	if (same[not_same[i].back()]) {
	    counter[i] = (counter[i] * factModed[same[not_same[i].back()]]) % MOD_ASKED;
	    same[not_same[i].back()] = 0;
	}
    }


    int64_t count = 1;

    std::string f;
    for (int i = 0; i < not_same.size(); i++) {
	f += not_same[i];
    }

    if (!is_valid(f)) {
	count = 0;
    }

    bool char_in_f[256] = {};
    for (int i = 0; i < f.length(); i++) {
	char_in_f[f[i]] = true;
    }

    for (int c = 'a'; c <= 'z'; c++) {
	if (same[c]) {
	    if (char_in_f[c]) {
		if (valid_same[c]) {
		    count = (count * factModed[same[c]]) % MOD_ASKED;
		} else {
		    count = 0;
		}
	    } else {
		counter.push_back(factModed[same[c]]);
	    }

	}
    }


    for (int i = 0; i < counter.size(); i++) {
	count = (count * counter[i]) % MOD_ASKED;
    }
    count = (count * factModed[counter.size()]) % MOD_ASKED;

    std::printf("Case #%d: %ld\n", t + 1, count);



}

int main() {

    factModed[0] = 1;

    for (int i = 1; i <= MAX_N; i++) {
	factModed[i] = (factModed[i - 1] * i) % MOD_ASKED;
    }

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test2(t);
    }

}
