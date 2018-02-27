#include <iostream>
#include <cstring>
#include <cstdint>

#define MAX_J 18
#define MAX_C 18

#define ABS(a) (((a) < 0) ? (-(a)) : (a))

#if 0

int compare(int *score1, int *score2, int score_length) {
	int sc1 = 0;
	int sc2 = 0;
	for (int i = 0; i < score_length; i++) {
		sc1 = sc1 * 10 + (score1[i] & 0x0F);
		sc2 = sc2 * 10 + (score2[i] & 0x0F);
	}

	return ABS(sc1 - sc2);
}

void do_test_rec(int *score1, int *score2, int *solution,
		int* solution_score, int score_length, int current) {

	if (current >= 2 * score_length) {

		int current = compare(score1, score2, score_length);
		if (*solution_score > current) {
			memcpy(solution, score1,
			       sizeof(int) * score_length);
			memcpy(solution + score_length, score2,
			       sizeof(int) * score_length);
			*solution_score = current;
		}

		return;
		
	}

	int *score_modif = (current >= score_length) ? score2 : score1;
	int left = current % score_length;

	if (!(score_modif[left] & 0x10)) {
		do_test_rec(score1, score2, solution, solution_score,
			    score_length, current + 1);
		return;
	}

	for (int i = 0; i < 10; i++) {
		score_modif[left] = (score_modif[left] & 0x10) | i;
		do_test_rec(score1, score2, solution,
			    solution_score, score_length,
			    current + 1);
	}

}


void do_test(int n) {

	std::string score1_str;
	std::cin >> score1_str;

	std::string score2_str;
	std::cin >> score2_str;

	int score_length = score1_str.length();

	int score1[MAX_C];
	int score2[MAX_J];

	for (int i = 0; i < score_length; i++) {
		if (score1_str[i] == '?') {
			score1[i] = 0x10;
		} else {
			score1[i] = score1_str[i] - '0';
		}
	}

	for (int i = 0; i < score_length; i++) {
		if (score2_str[i] == '?') {
			score2[i] = 0x10;
		} else {
			score2[i] = score2_str[i] - '0';
		}
	}

	std::cout << "Case #" << n + 1 << ": ";
	int solution[MAX_C];
	int solution_score = 0x7FFFFFF;
	do_test_rec(score1, score2, solution, &solution_score, score_length, 0);

	for (int i = 0; i < score_length; i++) {
		std::cout << (solution[i] & 0x0F);
	}
	std::cout << " ";
	for (int i = 0; i < score_length; i++) {
		std::cout << (solution[i + score_length] & 0x0F);
	}
	std::cout << std::endl;
}

#elif 0

int solution[MAX_C + MAX_J];
int64_t solution_score;

int64_t compare(int *scores, int score_length, int comparison_size) {
	int *score1 = scores;
	int *score2 = scores + score_length;

	int64_t sc1 = 0;
	int64_t sc2 = 0;
	for (int i = 0; i < comparison_size; i++) {
		sc1 = sc1 * 10 + (score1[i] & 0x0F);
		sc2 = sc2 * 10 + (score2[i] & 0x0F);
	}

	return ABS(sc1 - sc2);
}

static int64_t pow10[MAX_C + 1] = {
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000,
	10000000000,
	100000000000,
	1000000000000,
	10000000000000,
	100000000000000,
	1000000000000000,
	10000000000000000,
	100000000000000000,
	1000000000000000000
};

void do_test_rec(int *scores, int score_length, int current) {

	if (current >= 2 * score_length) {

		int64_t current = compare(scores, score_length, score_length);
		if (solution_score > current) {
			memcpy(solution, scores,
			       sizeof(int) * 2 * score_length);
			solution_score = current;
			std::cout << solution_score << std::endl;
		}

		return;
		
	}

	// Try to cut
	int fixed = current / 2;
	int64_t prx = compare(scores, score_length, fixed);
	if (prx >= 1 && (prx - 1) * pow10[score_length - fixed] + 1 > solution_score) {
		return;
	}

	int *num = scores + ((current & 0x1) ? score_length : 0) + (current / 2);



	if (!(*num & 0x10)) {
		do_test_rec(scores, score_length, current + 1);
		return;
	}

	for (int i = 0; i < 10; i++) {
		*num = (*num & 0x10) | i;
		do_test_rec(scores, score_length, current + 1);
	}

}


void do_test(int n) {

	std::string score1_str;
	std::cin >> score1_str;

	std::string score2_str;
	std::cin >> score2_str;

	int score_length = score1_str.length();

	int scores[2 * MAX_C];

	for (int i = 0; i < score_length; i++) {
		if (score1_str[i] == '?') {
			scores[i] = 0x10;
		} else {
			scores[i] = score1_str[i] - '0';
		}
	}

	for (int i = 0; i < score_length; i++) {
		if (score2_str[i] == '?') {
			scores[i + score_length] = 0x10;
		} else {
			scores[i + score_length] = score2_str[i] - '0';
		}
	}

	std::cout << "Case #" << n + 1 << ": ";
	solution_score = 0x7FFFFFF;
	do_test_rec(scores, score_length, 0);

	for (int i = 0; i < score_length; i++) {
		std::cout << (solution[i] & 0x0F);
	}
	std::cout << " ";
	for (int i = 0; i < score_length; i++) {
		std::cout << (solution[i + score_length] & 0x0F);
	}
	std::cout << std::endl;
}

#else

void do_test(int n) {

	std::string score1_str;
	std::cin >> score1_str;

	std::string score2_str;
	std::cin >> score2_str;

	char final_score1[MAX_C + 1];
	char final_score2[MAX_J + 1];
	
	std::strcpy(final_score1, score1_str.c_str());
 	std::strcpy(final_score2, score2_str.c_str());

	int score_length = score1_str.length();

	int conflict = 0;
	while (conflict < score_length) {
		if (final_score1[conflict] != '?' && final_score2[conflict] != '?' &&
			final_score1[conflict] != final_score2[conflict]) {
			break;
		}
		conflict++;
	}

	if (conflict < score_length) {

		char *max_score = (final_score1[conflict] > final_score2[conflict]) ? final_score1 : final_score2;
		char *min_score = (final_score1[conflict] < final_score2[conflict]) ? final_score1 : final_score2;

		int diff = max_score[conflict] - min_score[conflict];

		bool reverse = false;
		if (diff > 5) reverse = true;

		if (diff == 5) {

			int tm = conflict + 1;
			while (tm < score_length) {
				if (max_score[tm] != '?' && min_score[tm] != '?' && min_score[tm] != max_score[tm]) {
					reverse = min_score[tm] > max_score[tm];
					break;
				} else if (max_score[tm] != '?' && min_score[tm] == '?') {
					reverse = (max_score[tm] >= '5');
					break;
				} else if (min_score[tm] != '?' && max_score[tm] == '?') {
					reverse = (min_score[tm] <= '5');
					break;
				}
				tm++;
			}


		}

		if (reverse) {
			int tr = conflict - 1;
			while (tr >= 0) {
				if (min_score[tr] != '0' && max_score[tr] != '9' && (max_score[tr] != min_score[tr] || max_score[tr] == '?')) break;
				tr--;
			}

			if (tr >= 0) {
				if (max_score[tr] == '?' && min_score[tr] == '?') {
					max_score[tr] = '0';
					min_score[tr] = '1';
				} else if (max_score[tr] == '?') {
					max_score[tr] = min_score[tr] - 1;
				} else if (min_score[tr] == '?') {
					min_score[tr] = max_score[tr] + 1;
				}

				for (int i = tr + 1; i < conflict; i++) {
					if (max_score[i] == '?')
						max_score[i] = '9';
					if (min_score[i] == '?')
						min_score[i] = '0';
				}

				std::swap(min_score, max_score);


			}

		}


		// for (int i = 0; i < conflict; i++) {
		// 	if (max_score[i] == '?') {
		// 		max_score[i] = min_score[i];
		// 	} else if (min_score[i] == '?') {
		// 		min_score[i] = max_score[i];
		// 	}
		// }

		for (int i = conflict + 1; i < score_length; i++) {
			if (max_score[i] == '?')
				max_score[i] = '0';
			if (min_score[i] == '?')
				min_score[i] = '9';
		}


	}

	for (int i = 0; i < conflict; i++) {
		if (final_score1[i] == '?' && final_score2[i] == '?') {
			final_score1[i] = '0';
			final_score2[i] = '0';
		} else {
			if (final_score1[i] == '?') {
				final_score1[i] = final_score2[i];
			} else if (final_score2[i] == '?') {
				final_score2[i] = final_score1[i];
			}
		}
	}


	std::cout << "Case #" << n + 1 << ": ";
	std::cout << final_score1;
	std::cout << " ";
	std::cout << final_score2;
	std::cout << std::endl;
}


#if 0
1?23? 21???
19239 21000

A : ?98?9 - B : 11???
A[1] - B[1] > 5 => A[0] = B[0] + 1;
A : 098?9 - B : 11???
A[3] == ? && B[3] == ? && A < B => A[3] = 9 && B[3] = 0;










#endif

#endif

int main() {

	int T;
	std::cin >> T;

	for (int n = 0; n < T; n++) {
		do_test(n);
	}

	return 0;
}
