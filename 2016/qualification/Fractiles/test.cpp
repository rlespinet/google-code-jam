#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

bool incr(char *seq, int seq_length) {
	int i = 0;
	while (i < seq_length && seq[i] == 'G') {
		seq[i] = 'L';
		i++;
	}

	if (i < seq_length) {
		seq[i] = 'G';
		return false;
	} else {
		return true;
	}
	
}


int main(int argc, char **argv) {

	if (argc < 3) return -1;

	int initial_seq_length = std::atoi(argv[1]);
	int complexity = std::atoi(argv[2]);

	char *initial_seq = new char[initial_seq_length + 1];
	std::memset(initial_seq, 'L', initial_seq_length);
	initial_seq[initial_seq_length] = 0;

	int seq_size = std::pow(initial_seq_length, complexity);
	char *new_seq = new char[seq_size + 1];
	char *old_seq = new char[seq_size + 1];

	bool *witnesses = new bool[seq_size];
	std::memset(witnesses, 1, seq_size);

	bool first_time = true;
	for (;;) {

		std::memcpy(old_seq, initial_seq, initial_seq_length + 1);

		for (int i = 1; i < complexity; i++) {
			int bloc_size = std::pow(initial_seq_length, i);
			for (int j = 0; j < bloc_size; j++) {
				if (old_seq[j] == 'L') {
					std::memcpy(&new_seq[j * initial_seq_length], initial_seq, initial_seq_length);
				} else {
					std::memset(&new_seq[j * initial_seq_length], 'G', initial_seq_length);
				}
			}


			std::swap(old_seq, new_seq);
		}


		old_seq[seq_size] = 0;
		std::cout << initial_seq << " : " << old_seq << std::endl;

		if (!first_time) {
			for (int i = 0; i < seq_size; i++) {
				witnesses[i] = (witnesses[i] && (old_seq[i] == 'G'));
			}
		}

		bool overflow = incr(initial_seq, initial_seq_length);
		if (overflow) break;

		first_time = false;

	}

	for (int i = 0; i < initial_seq_length; i++) {
		std::cout << '#';
	}
	std::cout << " : ";

	for (int i = 0; i < seq_size; i++) {
		if (witnesses[i]) {
			std::cout << "^";
		} else {
			std::cout << " ";
		}
	}
	std::cout << std::endl;

	delete[] new_seq;
	delete[] old_seq;
	delete[] witnesses;

	delete[] initial_seq;
	
}
