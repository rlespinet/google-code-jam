#include <iostream>
#include <set>

#define MAX_N 1100

int get_full_number_rec(int neighbors[MAX_N][MAX_N], int neighbors_count[MAX_N], int node, int parent) {

    if (neighbors_count[node] == 1) {
	return 0;
    }

    if (neighbors_count[node] == 2 && parent != -1) {
	return 0;
    }

    int best_count[2] = {0, 0};
    for (int node_id = 0; node_id < neighbors_count[node]; node_id++) {
	int new_node = neighbors[node][node_id];
	if (new_node != parent) {
	    int count = get_full_number_rec(neighbors, neighbors_count, new_node, node);
	    if (count > best_count[0] || count > best_count[1]) {
		int id_min = (best_count[0] > best_count[1]) ? 1 : 0;
		best_count[id_min] = count;
	    }
	}
    }
    return 2 + best_count[0] + best_count[1];
}

void test(int t) {

    int neighbors[MAX_N][MAX_N];
    int neighbors_count[MAX_N] = {0};
    
    int N;
    std::cin >> N;
    for (int i = 0; i < N - 1; i++) {
	int X, Y;
	std::cin >> X;
	std::cin >> Y;
	neighbors[X - 1][neighbors_count[X - 1]++] = Y - 1;
	neighbors[Y - 1][neighbors_count[Y - 1]++] = X - 1;
    }


    int best_count = -1;
    int root = 0;
    for (int i = 0; i < N; i++) {

	// if (neighbors_count[i] >= 2) {
	    // Possibly root
	    int count = 1 + get_full_number_rec(neighbors, neighbors_count, i, -1);
	    if (count > best_count) {
		best_count = count;
		root = i;
	    }
	// }
    }

    int answer = N - best_count;
    // if (best_count == -1) {
    // 	switch (N) {
    // 	case 0:
    // 	    answer = 0;
    // 	    break;
    // 	case 1:
    // 	    answer = 1;
    // 	    break;
    // 	case 2:
    // 	    answer = 1;
    // 	    break;
    // 	}
    // }

    // if (answer == N + 1) {
    // 	std::cout << "LOL\n";
    // }


    std::cout << "Case #" << t + 1 << ": " << answer << std::endl;

}


int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

}
