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
#define ABS(_i) (((_i) > 0) ? (_i) : -(_i))

void compute_mean1(float *mean1, int N, int T) {

    for (int t = 0; t < T; t++) {

	int perm_f[MAX_N];
	for (int k = 0; k < N; k++) {
	    perm_f[k] = k;
	}

	int count[MAX_N] = {};
	for (int k = 0; k < N; k++) {
	    int p = rand() % (N - k) + k;
	    if (k != p) {
		count[k]++;
		count[p]++;
	    }
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

    // generate_input(50, 120);
    // return 0;

    srand(time(NULL));

    int N = 50;

    // float mean1[MAX_N] = {};
    // float mean2[MAX_N] = {};
    // compute_mean1(mean1, N, 10000);
    // compute_mean2(mean2, N, 10000);

    // float diff_d[MAX_N];

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
		// count[ABS(p - i)]++;
	    // }
	}

	assert(std::equal(perm_i, perm_i + N, perm_f));

	for (int i = 0; i < N; i++) {
	    std::printf("%d ", count[i]);
	}
	std::printf("\n");

    }


}
