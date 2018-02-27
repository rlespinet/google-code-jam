#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
#include <cassert>
#include <algorithm>
#include <ctime>

#define MAX_N 1000
#define MAX_T 120
#define SQUARE(_i) ((_i) * (_i))

void compute_mean1(float *mean1, int N, int T) {

    for (int t = 0; t < T; t++) {

	int perm_f[MAX_N];
	for (int k = 0; k < N; k++) {
	    perm_f[k] = k;
	}

	int count[MAX_N] = {};
	for (int k = 0; k < N; k++) {
	    int p = rand() % (N - k) + k;
	    // if (k != p) {
		count[k]++;
		count[p]++;
	    // }
	    std::swap(perm_f[k], perm_f[p]);
	}

	for (int i = 0; i < N; i++) {
	    mean1[i] += ((float) count[i]);
	}

    }

    for (int i = 0; i < N; i++) {
	mean1[i] /= ((float) T);
    }

}

void compute_mean2(float *mean2, int N, int T) {

    for (int t = 0; t < T; t++) {

	int perm_f[MAX_N];
	for (int k = 0; k < N; k++) {
	    perm_f[k] = k;
	}

	for (int k = 0; k < N; k++) {
	    int p = rand() % N;
	    std::swap(perm_f[k], perm_f[p]);
	}

	int num_map[MAX_N];

	int perm_i[MAX_N];
	for (int i = 0; i < N; i++) {
	    perm_i[i] = i;
	    num_map[i] = i;
	}

	int count[MAX_N] = {};
	for (int i = 0; i < N; i++) {
	    int p = num_map[perm_f[i]];
	    num_map[perm_i[p]] = i;
	    num_map[perm_i[i]] = p;
	    // if (perm_i[i] != perm_i[p]) {
		std::swap(perm_i[i], perm_i[p]);
		count[i]++;
		count[p]++;
	    // }
	}

	for (int i = 0; i < N; i++) {
	    mean2[i] += ((float) count[i]);
	}

    }

    for (int i = 0; i < N; i++) {
	mean2[i] /= ((float) T);
    }

}


void test1(int N, int T) {

    for (int t = 0; t < T; t++) {

	int perm_f[MAX_N];
	for (int k = 0; k < N; k++) {
	    perm_f[k] = k;
	}

	for (int k = 0; k < N; k++) {
	    int p = rand() % (N - k) + k;
	    std::swap(perm_f[k], perm_f[p]);
	}

	std::printf("%d\n", N);
	for (int i = 0; i < N; i++) {
	    std::printf("%d ", perm_f[i]);
	}
	std::printf("\n");


    }

}

void test2(int N, int T) {

    for (int t = 0; t < T; t++) {

	int perm_f[MAX_N];
	for (int k = 0; k < N; k++) {
	    perm_f[k] = k;
	}

	for (int k = 0; k < N; k++) {
	    int p = rand() % N;
	    std::swap(perm_f[k], perm_f[p]);
	}

	std::printf("%d\n", N);
	for (int i = 0; i < N; i++) {
	    std::printf("%d ", perm_f[i]);
	}
	std::printf("\n");

    }

}


void generate_input(int N, int T) {
    std::cout << T << std::endl;
    test1(N, T / 2);
    test2(N, T / 2);
}

int main() {

    // generate_input(1000, 120);
    // return 0;

    srand(time(NULL));

    int N = 1000;

    float mean1[MAX_N] = {};
    float mean2[MAX_N] = {};
    compute_mean1(mean1, N, 10000);
    compute_mean2(mean2, N, 10000);

    float diff_d[MAX_N];

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {

	int n;
	std::cin >> n;
	assert(n == N);

	int perm_f[MAX_N];
	for (int i = 0; i < N; i++) {
	    std::cin >> perm_f[i];
	}

	int num_map[MAX_N];

	int perm_i[MAX_N];
	for (int i = 0; i < N; i++) {
	    perm_i[i] = i;
	    num_map[i] = i;
	}

	int count[MAX_N] = {};
	for (int i = 0; i < N; i++) {
	    int p = num_map[perm_f[i]];
	    num_map[perm_i[p]] = i;
	    num_map[perm_i[i]] = p;
	    // if (perm_i[i] != perm_i[p]) {
		std::swap(perm_i[i], perm_i[p]);
		count[i]++;
		count[p]++;
	    // }
	}

	float d1 = 0.0f;
	float d2 = 0.0f;
	for (int i = 0; i < N; i+=2) {
	    d1 += SQUARE(count[i] - mean1[i]);
	    d2 += SQUARE(count[i] - mean2[i]);
	}

	diff_d[t] = d1 - d2;

    }

    // int order[MAX_T];
    // for (int i = 0; i < T; i++) {
    // 	order[i] = i;
    // }

    // std::sort(order, order + T, [&](int a, int b) {
    // 	    return diff_d[a] < diff_d[b];
    // 	});

    // bool choices[MAX_T];
    // for (int i = 0; i < T / 2; i++) {
    // 	choices[order[i]] = true;
    // 	choices[order[T - 1 - i]] = false;
    // }

    bool choices[MAX_T];
    for (int i = 0; i < T; i++) {
	choices[i] = (diff_d[i] < 0);
    }

    int good = 0;
    for (int i = 0; i < T; i++) {
	std::printf("Case #%d: ", i + 1);
	if (choices[i]) {
	    good++;
	    std::printf("GOOD");
	} else {
	    std::printf("BAD");
	}
	std::printf("\n");
    }

    std::printf("%d good - %d bad\n", good, T - good);


}
