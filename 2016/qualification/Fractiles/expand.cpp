#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

int main(int argc, char **argv) {

	if (argc < 3) return -1;

	int initial_seq_length = std::strlen(argv[1]);
	const char* initial_seq = argv[1];

	int complexity = std::atoi(argv[2]);
	
	std::cout << initial_seq << " " << complexity << std::endl;

	int seq_size = std::pow(initial_seq_length, complexity);
	char *new_seq = new char[seq_size + 1];
	char *old_seq = new char[seq_size + 1];

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

		new_seq[bloc_size * initial_seq_length] = 0;
		std::cout << new_seq << std::endl;

		std::swap(old_seq, new_seq);
	}

	delete[] new_seq;
	delete[] old_seq;
	
}
