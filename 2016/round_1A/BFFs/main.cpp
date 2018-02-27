#include <iostream>
#include <cstdio>

#define MAX_N 1000

#define MAX(a, b) (((a) < (b)) ? (b) : (a))

struct chaine_t {
	int beg;
	int end;
	int size;
};

int test_config(int *data, int *placement, int placement_size) {

	if (placement_size < 2) return 0;

	for (int i = 0; i < placement_size; i++) {
		int im1 = (i + placement_size - 1) % placement_size;
		int ip1 = (i + 1) % placement_size;
		if (data[placement[i]] != placement[im1] &&
		    data[placement[i]] != placement[ip1])
			return 0;
	}

	return 1;
}

int do_test4_rec(int *data, int *left, int N, int *placement, int placement_size) {


	int max = 0;

	if (test_config(data, placement, placement_size)) {
		max = MAX(max, placement_size);
	}

	if (placement_size < N) {

		for (int i = 0; i < N - placement_size; i++) {

			placement[placement_size] = left[i];

			std::swap(left[i], left[N - placement_size - 1]);

			int res = do_test4_rec(data, left, N, placement, placement_size+1);
			max = MAX(max, res);

			std::swap(left[i], left[N - placement_size - 1]);
		}

	}

	return max;
	
}

int do_test4(int t) {
	
	int N;
	std::cin >> N;

	int data[MAX_N];
	for (int i = 0; i < N; i++) {
		int current;
		std::cin >> current;
		data[i] = current - 1;
	}

	int left[MAX_N] = {0};
	for (int i = 0; i < N; i++) {
		left[i] = i;
	}

	int placement[MAX_N];
	return do_test4_rec(data, left, N, placement, 0);

}

int do_test5(int t) {

	int N;
	std::cin >> N;

	int max_noloop = 0;

	int data[MAX_N];
	for (int i = 0; i < N; i++) {
		int current;
		std::cin >> current;
		data[i] = current - 1;
	}

	int pointed[MAX_N] = {};
	for (int i = 0; i < N; i++) {
		pointed[data[i]] = 1;
	}

	int mutual[MAX_N];
	int mutual_size = 0;

	int chains[MAX_N] = {0};

	int seen[MAX_N] = {};
	int local_seen[MAX_N] = {};
	for (int i = 0; i < N; i++) {

		if (!pointed[i]) {
			int chain[MAX_N];
			int chain_size = 0;
			
			int current = i;
			while (!local_seen[current]) {
				local_seen[current] = 1;
				chain[chain_size++] = current;
				current = data[current];
			}

			int l = 0;
			for (l = 0; l < chain_size; l++) {
				if (chain[l] == current) {
					break;
				}
			}

			for (int i = 0; i < l; i++) {
				chains[data[chain[i]]] = MAX(chains[data[chain[i]]], i + 1);
				seen[chain[i]] = 1;
			}

			for (int i = 0; i < chain_size; i++) {
				local_seen[chain[i]] = 0;
			}

		}
	}

	int max_loop = 0;

	for (int i = 0; i < N; i++) {
		if (!seen[i]) {
			int current = i;
			int size = 0;
			do {
				seen[current] = 1;
				current = data[current];
				size++;
			} while (current != i);

			if (size == 2) {
				max_noloop += 2 + chains[i] + chains[data[i]];
			} else {
				max_loop = MAX(max_loop, size);
			}
		}
	}

	return MAX(max_noloop, max_loop);

}

int do_test3(int t) {

	int N;
	std::cin >> N;

	int max = 0;

	int data[MAX_N];
	for (int i = 0; i < N; i++) {
		int current;
		std::cin >> current;
		data[i] = current - 1;
	}

	int pointed[MAX_N] = {};
	for (int i = 0; i < N; i++) {
		pointed[data[i]] = 1;
	}

	int loops_array[MAX_N];
	int loops_array_size = 0;

	int mark[MAX_N] = {};
	int taken[MAX_N];
	int taken_size = 0;

	int seen[MAX_N] = {};
	int local_seen[MAX_N] = {};

	for (int i = 0; i < N; i++) {

		if (!pointed[i]) {
			int chain[MAX_N];
			int chain_size = 0;
			
			int current = i;
			while (!local_seen[current]) {
				local_seen[current] = 1;
				seen[current] = 1;
				chain[chain_size++] = current;
				current = data[current];
			}

			int l = 0;
			for (l = 0; l < chain_size; l++) {
				if (chain[l] == current) {
					break;
				}
			}
			
			int loop_size = chain_size - l;
			if (loop_size == 2) {
				max += chain_size;
				taken[taken_size++] = chain[chain_size - 1];
			} else if (loop_size) {
				loops_array[loops_array_size++] = loop_size;
			} else {
				mark[current] = MAX(mark[current], chain_size);
			}

			for (int i = 0; i < chain_size; i++) {
				local_seen[chain[i]] = 0;
			}

			// else if (loop_size) {
			// 	int j = loops_array_size + 1;
			// 	while (j > 0 && loops_array[j - 1] > loop_size) {
			// 		loops_array[j] = loops_array[j-1];
			// 	}
			// 	loops_array[j] = loop_size;
			// 	loops_array_size++;
			// }


		}
	}


	for (int i = 0; i < N; i++) {
		if (!seen[i]) {
			int current = i;
			int size = 0;
			do {
				seen[current] = 1;
				current = data[current];
				size++;
			} while (current != i);

			if (size == 2) {
				max += 2;
			} else {
				loops_array[loops_array_size++] = size;
			}
		}
	}

	for (int i = 0; i < taken_size; i++) {
		max += mark[taken[i]];
	}

	for (int i = 0; i < loops_array_size; i++) {
		max = MAX(max, loops_array[i]);
	}

	return max;

}

// int do_test2(int t) {

// 	int N;
// 	std::cin >> N;

// 	int data[MAX_N];
// 	for (int i = 0; i < N; i++) {
// 		int current;
// 		std::cin >> current;
// 		data[i] = current - 1;
// 	}

// 	chaine_t aperiodic[MAX_N];
// 	chaine_t periodic[MAX_N];
// 	int aperiodic_size = 0;
// 	int periodic_size = 0;

// 	int seen[MAX_N] = {};
// 	int seen_count = 0;

// 	while (seen_count < N) {
// 		if (seen[seen_count] == 0) {

// 			int this_chain[MAX_N];
// 			int this_chain_size = 0;

// 			int current = seen_count;
// 			while (seen[current] == 0) {
// 				this_chain[this_chain_size++] = current;
// 				seen[current] = 1;
// 				current = data[current];
// 			}

// 			int last = this_chain[this_chain_size - 1];
// 			int l = 0;
// 			for (l = 0; l < this_chain_size; l++) {
// 				if (this_chain[l] == data[last]) {
// 					break;
// 				}
// 			}
			
// 			if (l < this_chain_size) {
// 				periodic[periodic_size].beg = this_chain[l];
// 				periodic[periodic_size].end = last;
// 				periodic[periodic_size].size = this_chain_size - l;
// 				periodic_size++;
// 			}

// 			if (l > 0) {
// 				aperiodic[aperiodic_size].beg = this_chain[0];
// 				aperiodic[aperiodic_size].end = this_chain[l - 1];
// 				aperiodic[aperiodic_size].size = l;
// 				aperiodic_size++;
// 			}
			
// 		}
// 		seen_count++;
// 	}

// 	for (int i = 0; i < aperiodic_size; i++) {
// 		int j = i;
// 		chaine_t elt = aperiodic[i];

// 		while (j > 0 && data[elt.end] < data[aperiodic[j - 1].end]) {
// 			aperiodic[j] = aperiodic[j - 1];
// 			j--;
// 		}
// 		aperiodic[j] = elt;
// 	}

// 	int map_aperiodic[MAX_N] = 0;
// 	for (int i = 0; i < aperiodic_size; i++) {
// 		map_aperiodic[data[aperiodic[i].end]] = map_aperiodic[aperiodic[i].beg] + 
// 	}



// 	printf("APERIODIC : \n");
// 	for (int i = 0; i < aperiodic_size; i++) {
// 		printf("beg : %d - end : %d - size : %d\n", 
// 		       aperiodic[i].beg + 1, aperiodic[i].end + 1, aperiodic[i].size); 
// 	}


// 	printf("PERIODIC : \n");
// 	for (int i = 0; i < periodic_size; i++) {
// 		printf("beg : %d - end : %d - size : %d\n", 
// 		       periodic[i].beg + 1, periodic[i].end + 1, periodic[i].size); 
// 	}

	
	

// }

int do_test(int t) {

	int N;
	std::cin >> N;

	int data[MAX_N];
	for (int i = 0; i < N; i++) {
		int current;
		std::cin >> current;
		data[i] = current - 1;
	}

	chaine_t chaines[MAX_N];
	int chaines_size = 0;

	int seen[MAX_N] = {};
	int seen_count = 0;

	while (seen_count < N) {
		if (seen[seen_count] == 0) {
			int size = 1;
			int current = seen_count;
			seen[current] = 1;
			while (seen[data[current]] == 0) {
				current = data[current];
				seen[current] = 1;
				size++;
			}

			chaines[chaines_size].beg = seen_count;
			chaines[chaines_size].end = current;
			chaines[chaines_size].size = size;
			chaines_size++;
		}
		seen_count++;
	}

	int looping[MAX_N] = {};
	
	int max = 0;
	for (int i = 0; i < chaines_size;) {
		if (data[chaines[i].end] == chaines[i].beg) {
			max = MAX(chaines[i].size, max);
			std::swap(chaines[i], chaines[chaines_size - 1]);
			chaines_size--;
		} else {
			i++;
		}
	}

	int start = 0;
	int end = chaines_size - 1;
	while (start < end) {

		if (data[data[chaines[start].end]] == chaines[start].end) {
			std::swap(chaines[start], chaines[end]);
			end--;
		} else {
			start++;
		}
	}



	for (int i = 0; i <= end; i++) {
		int j = i;
		chaine_t elt = chaines[i];

		while (j > 0 && data[elt.end] < data[chaines[j - 1].end]) {
			chaines[j] = chaines[j - 1];
			j--;
		}
		chaines[j] = elt;
	}

	int aperiodic[MAX_N] = {};
	for (int i = 0; i <= end; i++) {
		aperiodic[data[chaines[i].end]] = 
			chaines[i].size + aperiodic[chaines[i].beg];
	}


	int local_max = 0;
	int sum = 0;
	for (int i = end + 1; i < chaines_size; i++) {
		sum += chaines[i].size;
		local_max = MAX(local_max, aperiodic[chaines[i].end]);
	}

	max = MAX(max, local_max + sum);

	return max;

}

int sort() {
	int array[] = {4,5,1,2,5,7,9,13,2};

	int end = (sizeof(array) / sizeof(int)) - 1;

	for (int i = 0; i <= end; i++) {
		int j = i;
		int elt = array[i];

		while (j > 0 && elt < array[j - 1]) {
			array[j] = array[j - 1];
			j--;
		}
		array[j] = elt;
	}

	for (int i = 0; i <= end; i++) {
		printf("%d ", array[i]);
	}

}

int main() {

	// sort();
	// return 0;

	int T;
	std::cin >> T;

	for (int i = 0; i < T; i++) {
		printf("Case #%d: %d\n", i + 1, do_test5(i));
		fprintf(stderr, "%d/%d\n", i + 1, T);
	}

	return 0;
}
