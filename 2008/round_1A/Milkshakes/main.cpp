#include <iostream>
#include <cstdlib>
#include <cstring>

#define MAX_N 2000
#define MAX_M 2000
#define MAX_SUM_T 8000

struct pair_t {
	int no;
	int malted;
};

struct client_t {
	int size;
	pair_t data[];
};

void do_test_semi_brute(int c) {
	int N;
	int M;
	std::cin >> N;
	std::cin >> M;

	int *malted = new int[MAX_N];
	int *clients = new int[MAX_SUM_T];

	int client_id = 0;

	for (int m = 0; m < M; m++) {
		int T;
		std::cin >> T;

		clients[client_id++] = T;

		for (int i = 0; i < T; i++) {
			int X;
			int Y;
			std::cin >> X;
			std::cin >> Y;

			clients[client_id++] = X - 1;
			clients[client_id++] = Y;

		}
	}

	bool impossible = false;
	bool one_more_turn = true;
	while (one_more_turn) {

		one_more_turn = false;
		for (int i = 0; i < client_id;) {
			client_t &client = *((client_t*) (&clients[i]));
			int size_client = 2 * client.size + 1;


			bool client_valid = false;
			int client_malted_id = -1;
			for (int j = 0; j < client.size; j++) {
				if (client.data[j].malted == 1) {
					client_malted_id = client.data[j].no;
				}

				if (client.data[j].malted == malted[client.data[j].no]) {
					client_valid = true;
				}

			}

			if (!client_valid) {
				if (client_malted_id == -1 || malted[client_malted_id]) {
					impossible = true;
					goto print;
				} else {
					malted[client_malted_id] = 1;
					one_more_turn = true;
					break;
				}
			}

			i += size_client;

		}

	}
print:
	std::cout << "Case #" << c + 1 << ":";

	if (impossible) {
		std::cout << " IMPOSSIBLE";
	} else {

		for (int i = 0; i < N; i++) {
			int output = malted[i];
			std::cout << " " << output;
		}

	}
	std::cout << std::endl;

}

void do_test(int c) {
	int N;
	int M;
	std::cin >> N;
	std::cin >> M;

	int maybe_malted[MAX_N] = {};

	int clients[MAX_SUM_T];
	int new_clients[MAX_SUM_T];
	int client_id = 0;

	for (int m = 0; m < M; m++) {
		int T;
		std::cin >> T;

		clients[client_id++] = T;

		for (int i = 0; i < T; i++) {
			int X;
			int Y;
			std::cin >> X;
			std::cin >> Y;

			clients[client_id++] = X - 1;
			clients[client_id++] = Y;

		}
	}

	for (int i = 0; i < client_id;) {
		client_t &client = *((client_t*) (&clients[i]));
		int size_client = 2 * client.size + 1;
		for (int j = 0; j < client.size; j++) {
			if (client.data[j].malted == 1) {
				maybe_malted[client.data[j].no]++;
			}
		}

		i += size_client;

	}


	bool one_more_turn = true;
	while (one_more_turn) {

		one_more_turn = false;
		int new_client_id = 0;

		for (int i = 0; i < client_id;) {
			client_t &client = *((client_t*) (&clients[i]));
			int size_client = 2 * client.size + 1;
			int j = 0;
			for (; j < client.size; j++) {

				if (client.data[j].malted) {
					continue;
				}

				if (!maybe_malted[client.data[j].no]) {
					break;
				}
			}


			if (j != client.size) {

				for (j = 0; j < client.size; j++) {
					if (client.data[j].malted) {
						maybe_malted[client.data[j].no]--;

						if (maybe_malted[client.data[j].no] == 0) {
							one_more_turn = true;
						}
					}

				}

			} else {

				std::memcpy(new_clients + new_client_id, clients + i, size_client * sizeof(int));
				new_client_id += size_client;
			}

			i += size_client;

		}

		std::swap(new_clients, clients);
		std::swap(new_client_id, client_id);

	}

	bool impossible = false;
	for (int i = 0; i < client_id;) {
		client_t &client = *((client_t*) (&clients[i]));
		int size_client = 2 * client.size + 1;
		int j = 0;

		impossible = true;
		for (; j < client.size; j++) {

			int malted_value = maybe_malted[client.data[j].no] ? 1 : 0;

			if (client.data[j].malted == malted_value) {
				impossible = false;
				break;
			}
		}

		if (impossible) break;

		i += size_client;
	}

	std::cout << "Case #" << c + 1 << ":";

	if (impossible) {
		std::cout << " IMPOSSIBLE";
	} else {

		for (int i = 0; i < N; i++) {
			int output = (maybe_malted[i])?1:0;
			std::cout << " " << output;
		}

	}
	std::cout << std::endl;


}


bool incr(int *array, int N) {

	int i = 0;
	while (array[i]) {
		array[i] = 0;
		i++;
	}
	if (i > N) return false;

	array[i] = 1;

	return true;

}


void do_test_brute(int c) {
	int N;
	int M;
	std::cin >> N;
	std::cin >> M;

	int maybe_malted[MAX_N] = {};
	int best_malted[MAX_N] = {};
	int best_sum = 0x7FFFFFFF;

	int clients[MAX_SUM_T];
	int new_clients[MAX_SUM_T];
	int client_id = 0;

	for (int m = 0; m < M; m++) {
		int T;
		std::cin >> T;

		clients[client_id++] = T;

		for (int i = 0; i < T; i++) {
			int X;
			int Y;
			std::cin >> X;
			std::cin >> Y;

			clients[client_id++] = X - 1;
			clients[client_id++] = Y;
		}
	}

	for (;;) {

		bool valid = true;
		for (int i = 0; i < client_id;) {
			client_t &client = *((client_t*) (&clients[i]));
			int size_client = 2 * client.size + 1;

			bool client_valid = false;
			for (int j = 0; j < client.size; j++) {

				if (client.data[j].malted == maybe_malted[client.data[j].no]) {
					client_valid = true;
					break;
				}

			}
			valid = client_valid && valid;

			i += size_client;

		}

		if (valid) {
			int sum = 0;
			for (int i = 0; i < N; i++) {
				sum += maybe_malted[i];
			}
			if (sum < best_sum) {
				std::swap(best_malted, maybe_malted);
				best_sum = sum;
			}
		}


		if (!incr(maybe_malted, N)) {
			break;
		}


	}

	std::cout << "Case #" << c + 1 << ":";

	if (best_sum == 0x7FFFFFFF) {
		std::cout << " IMPOSSIBLE";
	} else {

		for (int i = 0; i < N; i++) {
			int output = (best_malted[i])?1:0;
			std::cout << " " << output;
		}

	}
	std::cout << std::endl;

}


int main() {

	int C;
	std::cin >> C;

	for (int i = 0; i < C; i++) {
            // do_test_semi_brute(i);
            do_test(i);
	}

}
