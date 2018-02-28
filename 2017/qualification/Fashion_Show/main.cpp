#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#define MAX_N 100

bool is_valid(char *array, int N) {

    int col[MAX_N] = {};
    int row[MAX_N] = {};

    int diag[2 * MAX_N - 1] = {};
    int anti_diag[2 * MAX_N - 1] = {};


    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (array[i * N + j] == 'x' ||
		array[i * N + j] == 'o') {
		col[j]++;
		row[i]++;
	    }

	    if (array[i * N + j] == '+' ||
		array[i * N + j] == 'o') {
		diag[i + j]++;
		anti_diag[j - i + N - 1]++;
	    }
	}
    }

    for (int i = 0; i < N; i++) {
	if (col[i] > 1) return false;
	if (row[i] > 1) return false;
    }

    for (int i = 0; i < 2 * N - 1; i++) {
	if (diag[i] > 1) return false;
	if (anti_diag[i] > 1) return false;
    }

    return true;

}

int score(char *array, int N) {
    int res = 0;
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {

	    switch (array[i * N + j]) {
	    case 'o':
		res+=2;
		break;
	    case 'x':
	    case '+':
		res+=1;
		break;
	    }
	}
    }
    return res;
}

void compute(char *array, int N) {
    int col[MAX_N];
    int row[MAX_N];

    int diag[2 * MAX_N - 1];
    int anti_diag[2 * MAX_N - 1];

    // int col_count[MAX_N];
    // int row_count[MAX_N];
    // int diag_count[MAX_N];
    // int anti_diag_count[MAX_N];

    for (int i = 0; i < N; i++) {
	col[i] = -1;
	row[i] = -1;
    }

    for (int i = 0; i < 2 * N - 1; i++) {
	diag[i] = -1;
	anti_diag[i] = -1;
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (array[i * N + j] == 'x' ||
		array[i * N + j] == 'o') {
		col[j] = i;
		row[i] = j;
	    }

	    if (array[i * N + j] == '+' ||
		array[i * N + j] == 'o') {
		diag[i + j] = j - i + N - 1;
		anti_diag[j - i + N - 1] = i + j;
	    }

	}
    }

    // Place +
    std::vector<int> choices;
    choices.push_back(N - 1);

    for (int i = 0; i < N; i++) {
	if (diag[i] == -1) {

	    for (int k = 0; k < choices.size(); k++) {
		if (anti_diag[choices[k]] == -1) {
		    diag[i] = choices[k];
		    anti_diag[choices[k]] = i;
		    break;
		}

	    }

	}

	if (diag[2 * N - 2 - i] == -1) {

	    for (int k = 0; k < choices.size(); k++) {
		if (anti_diag[choices[k]] == -1) {
		    diag[2 * N - 2 - i] = choices[k];
		    anti_diag[choices[k]] = 2 * N - 2 - i;
		    break;
		}
	    }

	}

	for (int k = 0; k < choices.size(); k++) {
	    choices[k]--;
	}
	choices.push_back(N + i);

    }





    int free_row[MAX_N] = {};
    int free_col[MAX_N] = {};

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (array[i * N + j] != '.') {
		free_row[i]++;
		free_col[j]++;
	    }
	}
    }


    std::vector<int> row_list;
    std::vector<int> col_list;

    for (int i = 0; i < N; i++) {
	if (row[i] == -1 && free_row[i] < N) {
	    row_list.push_back(i);
	}

	if (col[i] == -1 && free_col[i] < N) {
	    col_list.push_back(i);
	}
    }


    std::sort(row_list.begin(), row_list.end(),
	      [&](int i, int j) {return free_row[i] < free_row[j];});
    std::sort(col_list.begin(), col_list.end(),
	      [&](int i, int j) {return free_col[i] < free_col[j];});

    // Place x
    for (int i = 0; i < std::min(row_list.size(), col_list.size()); i++) {
	row[row_list[i]] = col_list[i];
	col[col_list[i]] = row_list[i];
    }

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (row[i] == j) {
		if (array[i * N + j] == '+' ||
		    array[i * N + j] == 'o') {
		    array[i * N + j] = 'o';
		} else {
		    if (diag[i + j] == -1 &&
			anti_diag[j - i + N - 1] == -1) {
		    } else {
			array[i * N + j] = 'x';
		    }

		}
	    }

	    if (diag[i + j] == j - i + N - 1) {
		if (array[i * N + j] == 'x' ||
		    array[i * N + j] == 'o') {
		    array[i * N + j] = 'o';
		} else {

		    if (row[i] == -1 &&
			col[j] == -1) {
			array[i * N + j] = 'o';
		    } else {
			array[i * N + j] = '+';
		    }
		}

	    }


	}
    }




}


void random_check(char *array, int N) {

    char data[2 *MAX_N * MAX_N];
    char *rand_array = &data[0];
    char *best_rand_array = &data[MAX_N];

    int best_score = score(array, N);
    std::memcpy(best_rand_array, array, N * N * sizeof(char));

    for (int w = 0; w < 100; w++) {

	std::memcpy(rand_array, array, N * N * sizeof(char));

	for (int x = 0; x < 1000; x++) {

	    int i = rand() % N;
	    int j = rand() % N;

	    char m;
	    if (rand_array[i*N + j] == '.') {
		m = (rand() % 2) ? 'x' : '+';
	    } else if (rand_array[i*N + j] == 'o') {
		continue;
	    } else {
		m = 'o';
	    }

	    char r = rand_array[i*N + j];
	    rand_array[i*N + j] = m;
	    if (!is_valid(rand_array, N)) {
		rand_array[i*N + j] = r;
	    }

	}

	int new_score = score(rand_array, N);
	if (new_score > best_score) {
	    best_score = new_score;
	    std::swap(best_rand_array, rand_array);
	}


    }

    std::cout << "best_rand_array : " << best_score << std::endl;
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    	    std::cout << best_rand_array[i * N + j];
    	}
    	std::cout << std::endl;
    }


}

void test(int t) {

    int N, M;
    std::cin >> N;
    std::cin >> M;

    char array[MAX_N * MAX_N];
    std::memset(array, '.', N * N * sizeof(char));

    for (int m = 0; m < M; m++) {
	char model;
	std::cin >> model;

	int R, C;
	std::cin >> R;
	std::cin >> C;
	array[(R - 1) * N + (C - 1)] = model;
    }

    char new_array[MAX_N * MAX_N];
    std::memcpy(new_array, array, sizeof(char) * N * N);

    // random_check(array, N);


    // Compute row, col and diags states
    compute(new_array, N);


    std::cout << "Case #" << t + 1 << ": ";

    int count = 0;
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (new_array[N * i + j] != array[N * i + j]) {
		count++;
	    }
	}

    }

    std::cout << score(new_array, N) << " " << count << std::endl;

    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (new_array[N * i + j] != array[N * i + j]) {
		std::cout << new_array[N * i + j] << " " << i + 1 << " " << j + 1 << std::endl;
	    }
	}

    }

    // for (int i = 0; i < N; i++) {
    // 	for (int j = 0; j < N; j++) {
    // 	    switch (pos[i * N + j]) {
    // 	    case 0:
    // 		std::cout << ".";
    // 		break;
    // 	    case CROSS_FLAG:
    // 		std::cout << "x";
    // 		break;
    // 	    case PLUS_FLAG:
    // 		std::cout << "+";
    // 		break;
    // 	    case CROSS_FLAG | PLUS_FLAG:
    // 		std::cout << "o";
    // 		break;
    // 	    }
    // 	}
    // 	std::cout << std::endl;
    // }


    // for (int i = 0; i < N; i++) {
    // 	for (int j = 0; j < N; j++) {
    // 	    std::cout << new_array[i * N + j];
    // 	}
    // 	std::cout << std::endl;
    // }


}

int main(int argc, char **argv) {

    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++) {
	test(t);
    }


    return 0;
}
