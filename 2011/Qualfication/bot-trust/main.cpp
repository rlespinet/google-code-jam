#include <iostream>
#include <cmath>

#define MAX_N 1000

// void test(int t) {

//     int N;
//     std::cin >> N;

//     char rob[MAX_N];
//     int pos[MAX_N];

//     for (int i = 0; i < N; i++) {
// 	std::cin >> rob[i];
// 	std::cin >> pos[i];
//     }

//     int blue_pos = 0;
//     int orange_pos = 0;

//     int blue_time = 0;
//     int orange_time = 0;
//     for (int i = 0; i < N; i++) {
// 	if (rob[i] == 'B') {
// 	    int time_needed = std::max(0, pos[i] - blue_pos);
// 	    if (blue_time >= time_needed) {
// 		blue_time -= time_needed;
// 	    } else {

// 		orange_time += time_needed - blue_time;
// 		blue_time = 0;
// 	    }
// 	    blue_pos = pos[i];
// 	} else {
// 	    int time_needed = std::max(0, pos[i] - orange_pos);
// 	    if (orange_time >= time_needed) {
// 		orange_time -= time_needed;
// 	    } else {
// 		blue_time += time_needed - blue_time;
// 		blue_time = 0;
// 	    }
// 	    orange_pos = pos[i];
// 	}
//     }

//     std::printf("Case #%d: %d\n", t + 1, time);
// }

void test(int t) {

    int N;
    std::cin >> N;

    char rob[MAX_N];
    int pos[MAX_N];

    for (int i = 0; i < N; i++) {
	std::cin >> rob[i];
	std::cin >> pos[i];
    }

    int time = 0;
    int orange_pos = 1;
    int blue_pos = 1;
    for (int i = 0; i < N; i++) {
	int *robot_pos = &orange_pos;
	int *oth_pos = &blue_pos;
	char oth_letter = 'B';
	if (rob[i] == 'B') {
	    robot_pos = &blue_pos;
	    oth_pos = &orange_pos;
	    oth_letter = 'O';
	}

	int time_inc = std::abs(*robot_pos - pos[i]) + 1;
	time += time_inc;
	*robot_pos = pos[i];
	for (int j = i + 1; j < N; j++) {
	    if (rob[j] == oth_letter) {
		if (std::abs(*oth_pos - pos[j]) <= time_inc) {
		    *oth_pos = pos[j];
		} else {
		    *oth_pos += (*oth_pos < pos[j]) ? time_inc : -time_inc;
		}
		break;
	    }
	}
    }

    std::printf("Case #%d: %d\n", t + 1, time);
}



int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

    return 0;
}
