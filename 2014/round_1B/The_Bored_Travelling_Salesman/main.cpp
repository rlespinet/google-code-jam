#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <deque>

#define MAX_N 50

void test(int t) {

    int N;
    int M;
    std::cin >> N;
    std::cin >> M;

    int postal[MAX_N];
    for (int i = 0; i < N; i++) {
	std::cin >> postal[i];
    }

    std::vector< std::vector<int> > flight(N);
    for (int i = 0; i < M; i++) {
	int a, b;
	std::cin >> a;
	std::cin >> b;
	flight[a - 1].push_back(b - 1);
	flight[b - 1].push_back(a - 1);
    }

    int start_id = 0;
    for (int i = 1; i < N; i++) {
	if (postal[i] < postal[start_id]) {
	    start_id = i;
	}
    }

    std::set<int> left;
    for (int i = 0; i < N; i++) {
	left.insert(i);
    }
    left.erase(start_id);

    std::set<int> visited;
    std::vector<int> flight_stack;
    std::vector<int> order_list;
    visited.insert(start_id);
    flight_stack.push_back(start_id);
    order_list.push_back(start_id);

    while (!left.empty()) {

	int next_id = -1;
	int stack_id = -1;

	std::vector<std::set<int> > direct_accessible(flight_stack.size());
	std::vector<std::set<int> > accessible(flight_stack.size());
	for (int k = 0; k <  flight_stack.size(); k++) {

	    for (int m = 0; m < flight[flight_stack[k]].size(); m++) {
		if (visited.find(flight[flight_stack[k]][m]) == visited.end()) {
		    direct_accessible[k].insert(flight[flight_stack[k]][m]);
		}
	    }

	    accessible[k] = direct_accessible[k];

	    bool grow = true;
	    while (grow) {
		grow = false;
		for (auto it = accessible[k].begin(); it != accessible[k].end(); it++) {
		    for (int m = 0; m < flight[*it].size(); m++) {
			if (visited.find(flight[*it][m]) == visited.end()) {
			    if (accessible[k].insert(flight[*it][m]).second) {
				grow = true;
			    }
			}
		    }

		}
	    }

	}


	for (int k = flight_stack.size() - 1; k >= 0 ; k--) {

	    std::set<int> total_accessible;
	    for (int l = 0; l <= k; l++) {
		for (auto it = accessible[l].begin(); it != accessible[l].end(); ++it) {
		    total_accessible.insert(*it);
		}
	    }

	    bool all_accessible = true;
	    for (auto it = left.begin(); it != left.end(); ++it) {
		if (total_accessible.find(*it) == total_accessible.end()) {
		    all_accessible = false;
		    break;
		}
	    }

	    if (all_accessible) {
		for (auto it = direct_accessible[k].begin(); it != direct_accessible[k].end(); ++it) {
		    if (next_id == -1 || postal[*it] < postal[next_id]) {
			next_id = *it;
			stack_id = k;
		    }
		}
	    }

	}

	assert(next_id != -1);

	flight_stack.resize(stack_id + 1);
	flight_stack.push_back(next_id);
	visited.insert(next_id);
	order_list.push_back(next_id);
	left.erase(next_id);

    }

    std::printf("Case #%d: ", t + 1);
    for (int i = 0; i < order_list.size(); i++) {
	std::printf("%d", postal[order_list[i]]);
    }
    std::printf("\n");
}


int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

    return 0;
}
