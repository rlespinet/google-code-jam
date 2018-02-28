#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#define MAX_N 1000

void compute_permutations_rec(int *array, int size, int left_size,
			      std::vector<std::vector<int>> &perm) {

    if (left_size == 0) {
	std::vector<int> new_perm(size);
	std::copy(array, array + size, new_perm.begin());
	perm.push_back(new_perm);
	return;
    }

    for (int i = 0; i < left_size; i++) {
	std::swap(array[size], array[size + i]);
	compute_permutations_rec(array, size + 1, left_size - 1, perm);
	std::swap(array[size], array[size + i]);
    }

}

void compute_permutations(int N, std::vector<std::vector<int>> &perm) {

    int array[MAX_N];
    for (int i = 0; i < N; i++) {
	array[i] = i;
    }

    compute_permutations_rec(array, 0, N, perm);

}

void count_rec(std::map<std::vector<int>, int> &perm_count,
	       std::vector<int> &array, int N, int i) {

    if (i >= N) {
	perm_count[array]++;
	return;
    }

    for (int k = 0; k < N; k++) {
	std::swap(array[i], array[k]);
	count_rec(perm_count, array, N, i + 1);
	std::swap(array[i], array[k]);
    }


}

void count(std::vector<std::vector<int>> &perm, int N) {

    std::map<std::vector<int>, int> perm_count;
    for (int i = 0; i < perm.size(); i++) {
	perm_count[perm[i]] = 0;
    }

    std::vector<int> array(N);
    for (int i = 0; i < N; i++) {
	array[i] = i;
    }

    count_rec(perm_count, array, N, 0);

    for (auto it = perm_count.begin(); it != perm_count.end(); ++it) {
	const std::vector<int>& v = it->first;
	std::printf("%3d:", it->second);
	for (int i = 0; i < v.size(); i++) {
	    std::printf(" %d", v[i]);
	}
	std::printf("\n");

    }


}


int main() {

    int N = 5;

    std::vector<std::vector<int>> perm;
    compute_permutations(N, perm);
    count(perm, N);

    // for (int i = 0; i < perm.size(); i++) {
    // 	for (int k = 0; k < N; k++) {
    // 	    std::printf("%d ", perm[i][k]);
    // 	}
    // 	std::printf("\n");
    // }

    return 0;
}
