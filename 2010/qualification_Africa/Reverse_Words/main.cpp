#include <iostream>
#include <limits>
#include <vector>
#include <cstring>

#define MAX_L 1000
#define MAX_N 100

void do_test(int n) {
	
	char buffer_in[MAX_L + 1];
	char buffer_out[MAX_L + 1];

	int buffer_out_size = 0;

	std::cin.getline(buffer_in, MAX_L);

	std::vector<int> spaces_pos;
	spaces_pos.push_back(-1);

	for (int i = 0; i < MAX_L; i++) {

		if (buffer_in[i] == ' ' ||
		    buffer_in[i] == '\0') {
			spaces_pos.push_back(i);
			
			if (buffer_in[i] == '\0') break;

		}
	}

	for (int i = spaces_pos.size() - 2; i >= 0; i--) {

		int added = spaces_pos[i+1] - spaces_pos[i] - 1;
		std::memcpy(&buffer_out[buffer_out_size], &buffer_in[spaces_pos[i] + 1], added);
		buffer_out_size += added;
		buffer_out[buffer_out_size++] = ' ';

	}

	buffer_out[buffer_out_size++] = 0;

	std::cout << "Case #" << n + 1 << ": ";
	std::cout << buffer_out << std::endl;

}

int main() {
	int N;
	std::cin >> N;
	std::cin.ignore(0xFFFFFFFF, '\n');
	for (int n = 0; n < N; n++) {
		do_test(n);
	}

	return 0;
}
