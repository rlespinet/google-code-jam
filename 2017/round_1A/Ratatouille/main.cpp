#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

#define MAX_N 51
#define MAX_P 51

int max_count;

void test_rec(int recipe[MAX_N], int ingredients[MAX_N][MAX_P], int N, int i, int P);

void find_best(int recipe[MAX_N], int ingredients[MAX_N][MAX_P], int N, int i, int P, int j, int inf, int sup) {

    if (j >= N) {
	max_count = std::max(max_count, i + 1);
	test_rec(recipe, ingredients, N, i + 1, P);
	return;
    }

    for (int k = i; k < P; k++) {
	int this_inf = std::ceil((float) ingredients[j][k] / (float) recipe[j] / 1.1f);
	int this_sup = std::floor((float) ingredients[j][k] / (float) recipe[j] / 0.9f);

	if (this_inf <= this_sup && this_inf <= sup && this_sup >= inf) {
	    std::swap(ingredients[j][i], ingredients[j][k]);
	    find_best(recipe, ingredients, N, i, P, j + 1, inf, sup);
	    std::swap(ingredients[j][i], ingredients[j][k]);
	}


    }



}

void test_rec(int recipe[MAX_N], int ingredients[MAX_N][MAX_P], int N, int i, int P) {

    if (i >= P) return;

    for (int j = i; j < P; j++) {

	std::swap(ingredients[0][i], ingredients[0][j]);

	int inf = std::ceil((float) ingredients[0][i] / (float) recipe[0] / 1.1f);
	int sup = std::floor((float) ingredients[0][i] / (float) recipe[0] / 0.9f);

	if (inf <= sup) {
	    find_best(recipe, ingredients, N, i, P, 1, inf, sup);
	    if (max_count == P) return;
	}

	std::swap(ingredients[0][i], ingredients[0][j]);

    }

}

void test(int t) {

    int N;
    std::cin >> N;

    int P;
    std::cin >> P;

    int recipe[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> recipe[i];
    }

    int ingredients[MAX_N][MAX_P];

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < P; j++) {
	    std::cin >> ingredients[i][j];
	}
    }

    max_count = 0;
    test_rec(recipe, ingredients, N, 0, P);

    std::printf("Case #%d: %d", t + 1, max_count);
    std::printf("\n");
}


struct borne {
    int inf;
    int sup;
};

void test2(int t) {

    int N;
    std::cin >> N;

    int P;
    std::cin >> P;

    int recipe[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> recipe[i];
    }

    int ingredients[MAX_N][MAX_P];

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < P; j++) {
	    std::cin >> ingredients[i][j];
	}
    }


    borne bornes[MAX_N][MAX_P];
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < P; j++) {
	    bornes[i][j].inf = std::ceil((float) ingredients[i][j] / (float) recipe[i] / 1.1f);
	    bornes[i][j].sup = std::floor((float) ingredients[i][j] / (float) recipe[i] / 0.9f);
	}
    }

    for (int i = 0; i < N; i++) {
	std::sort(bornes[i], bornes[i] + P, [] (borne &p, borne &q) {return (p.inf < q.inf)?true:p.sup < q.sup;});
    }

    int cursor[MAX_N];
    int next_cursor[MAX_N];
    for (int i = 0; i < N; i++) {
	cursor[i] = 0;
    }

    int count = 0;
    for (int j = 0; j < P; j++) {

	int found = 0;

	int inf = bornes[0][j].inf;
	int sup = bornes[0][j].sup;

	if (inf > sup) continue;

	for (int i = 1; i < N; i++) {

	    for (int k = cursor[i]; k < P; k++) {

		int this_inf = bornes[i][k].inf;
		int this_sup = bornes[i][k].sup;

		if (this_inf <= this_sup && this_inf <= sup && this_sup >= inf) {
		    next_cursor[i] = k + 1;
		    found++;
		    break;
		}

	    }

	}

	// if (std::all_of(next_cursor, next_cursor + N, [] (int i) {return i != -1;})) {
	if (found >= (N - 1)) {
	    for (int i = 0; i < N; i++) {
		cursor[i] = next_cursor[i];
	    }
	    count++;
	}


    }

    std::printf("Case #%d: %d", t + 1, count);
    std::printf("\n");
}


int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test2(t);
    }

}
