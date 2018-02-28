#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

#define MAX_R 25
#define MAX_C 25

void test_rec(std::string *cake, int i, int j, int R, int C) {

    int first_k = -1;
    int first_l = -1;

    int second_k = -1;
    int second_l = -1;
    for (int k = i; k < R; k++) {
	for (int l = j; l < C; l++) {
	    if (cake[k][l] != '?') {
		if (first_k == -1) {
		    first_k = k;
		    first_l = l;
		} else {
		    second_k = k;
		    second_l = l;
		    goto end;
		}
	    }
	}
    }
end:
    if (first_k == -1) return;

    if (second_k == -1) {
	for (int k = i; k < R; k++) {
	    for (int l = j; l < C; l++) {
		cake[k][l] = cake[first_k][first_l];
	    }
	}
    } else {
	if (first_k != second_k) {
	    test_rec(cake, i, j, first_k + 1, C);
	    test_rec(cake, first_k + 1, j, R, C);
	} else {
	    test_rec(cake, i, j, R, first_l + 1);
	    test_rec(cake, i, first_l + 1, R, C);
	}
    }

}

void test(int t) {

    int R, C;
    std::cin >> R;
    std::cin >> C;

    std::string cake[MAX_R];
    for (int i = 0; i < R; i++) {
	std::cin >> cake[i];
    }

    test_rec(cake, 0, 0, R, C);

    std::printf("Case #%d:\n", t + 1);
    for (int i = 0; i < R; i++) {
	std::cout << cake[i] << std::endl;
    }
    std::printf("\n");
}

int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

}
