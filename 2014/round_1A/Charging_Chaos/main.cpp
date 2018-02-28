#include <iostream>
#include <cstring>
#include <map>

#define MAX_N 200
#define MAX_L 50

void test(int t) {

    int N, L;
    std::cin >> N;
    std::cin >> L;

    int outlet[MAX_N];
    int devices[MAX_N];

    std::memset(outlet, 0, sizeof(outlet));
    std::memset(devices, 0, sizeof(devices));
    
    std::string S;
    for (int i = 0; i < N; i++) {
	std::cin >> S;
	for (int j = 0; j < S.length(); j++) {
	    outlet[i] = (outlet[i] << 1) | ((S[j] == '1') ? 1 : 0);
	}
    }

    for (int i = 0; i < N; i++) {
	std::cin >> S;
	for (int j = 0; j < S.length(); j++) {
	    devices[i] = (devices[i] << 1) | ((S[j] == '1') ? 1 : 0);
	}
    }

    std::map<int, int> m;
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    auto it = m.find(outlet[i] ^ devices[j]);
	    if (it == m.end()) {
		it = m.insert(std::pair<int, int>(outlet[i] ^ devices[j], 0)).first;
	    }
	    (it->second)++;
	    // m.insert(outlet[i] ^ devices[i], val + 1);
	}
    }

    int best_count1 = L + 1;
    for (auto it = m.begin(); it != m.end(); ++it) {
	if (it->second == N) {
	    int count1 = 0;
	    for (int i = 0; i < L; i++) {
		count1 += (it->first & (1 << i)) ? 1 : 0;
	    }
	    if (count1 < best_count1) {
		best_count1 = count1;
	    }
	}
    }

    std::cout << "Case #" << t + 1 << ": ";
    if (best_count1 == L + 1) {
	std::cout << "NOT POSSIBLE" << std::endl;
    } else {
	std::cout << best_count1 << std::endl;
    }
    
}

int main() {

    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
	test(i);
    }

    return 0;

}
