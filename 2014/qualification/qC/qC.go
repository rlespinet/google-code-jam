package main;

import (
	"fmt"
)

func expand(array []byte, R, C, i, j int) {

	if (array[i * C + j] == '.') {

		count := 0;
		for k := -1; k <= 1; k++ {
			for l := -1; l <= 1; l++ {
				if (i + k < 0 || i + k >= R) {
					continue;
				}
				if (j + l < 0 || j + l >= C) {
					continue;
				}

				if array[(i + k) * C + (j + l)] == '*' {
					count++;
				}

			}
		}

		array[i * C + j] = '0' + byte(count);

		if (count == 0) {
			for k := -1; k <= 1; k++ {
				for l := -1; l <= 1; l++ {
					if (i + k < 0 || i + k >= R) {
						continue;
					}
					if (j + l < 0 || j + l >= C) {
						continue;
					}

					expand(array, R, C, i + k, j + l);

				}
			}
		}


	}



}

func minesweeper_naive_test(array []byte, R, C int) bool {

	test_array := make([]byte, R * C);

	for i := 0; i < R; i++ {

		for j := 0; j < C; j++ {

			if array[i * C + j] == '.' {

				for k := 0; k < R * C; k++ {
					test_array[k] = array[k];
				}

				expand(test_array, R, C, i, j);

				ok := true;
			outer:
				for k := 0; k < R; k++ {

					for l := 0; l < C; l++ {

						if test_array[k * C + l] == '.' {
							ok = false;
							break outer;
						}

					}

				}

				if ok {
					array[i * C + j] = 'c';
					return true;
				}


			}
		}

	}

	return false;

}

func minesweeper_naive_rec(array []byte, R, C, M int, i int) bool {


	if (M == 0) {
		return minesweeper_naive_test(array, R, C);
	} else	if (i >= R * C) {
		return false;
	} else {

		array[i] = '*';
		result := minesweeper_naive_rec(array, R, C, M - 1, i + 1);
		if result {
			return true;
		}

		array[i] = '.';
		result = minesweeper_naive_rec(array, R, C, M, i + 1);
		return result;

	}

}

func minesweeper_naive(R, C, M int) ([]byte, bool, bool) {

	array := make([]byte, R * C);
	for i := 0; i < R * C; i++ {
		array[i] = '.';
	}

	result := minesweeper_naive_rec(array, R, C, M, 0);
	return array, result, false;

}


func minesweeper(R, C, M int) ([]byte, bool, bool) {

	left := R * C - M;

	if (left < 0) {
		// impossible
		return nil, false, false;
	}

	array := make([]byte, R * C);
	for i := 0; i < R * C; i++ {
		array[i] = '*';
	}

	if (left == 1) {
		array[0] = 'c';
		return array, true, false;
	}

	transpose := false;
	if (C < R) {
		R, C = C, R;
		transpose = true;
	}

	if (R == 1) {

		for i := 0; i < left; i++ {
			array[i] = '.';
		}
		array[0] = 'c';
		return array, true, transpose;


	} else if (R == 2) {

		if (left < 4) {
			// impossible
			return nil, false, false;
		} else if (left % 2 == 0) {
			for i := 0; i < left / 2; i++ {
				array[0 * C + i] = '.';
				array[1 * C + i] = '.';
			}
			array[0] = 'c';
			return array, true, transpose;
		} else {

			return nil, false, false;
			// if (C >= M / 2 + 4) {

			// 	for i := 0; i < R * C; i++ {
			// 		array[i] = '.';
			// 	}

			// 	for i := 0; i < M / 2; i++ {
			// 		array[0 * C + i] = '*';
			// 		array[1 * C + i] = '*';
			// 	}

			// 	array[0 * C + M / 2 + 1] = 'c';
			// 	array[0 * C + C - 1] = '*';
			// 	return array, true, transpose;


			// } else {
			// 	// impossible
			// 	return nil, false, false;
			// }


		}

	} else {

		if (left < 4) {
			// impossible
			return nil, false, transpose;
		} else {

			for i := 0; i < 2; i++ {
				for j := 0; j < 2; j++ {
					array[i * C + j] = '.';
				}

			}

			left -= 4;

			cur_row := 2;
			cur_col := 2;

			alt := true;
			for {

				// for j := 0; j < R; j++ {
				// 	for k := 0; k < C; k++ {
				// 		fmt.Printf("%c", array[j * C + k]);
				// 	}
				// 	fmt.Println();
				// }


				if (left < 2) {
					break;
				}

				if (cur_col == C && cur_row == R) {
					break;
				}

				if (cur_col == C) {

					array[cur_row * C + 0] = '.';
					array[cur_row * C + 1] = '.';
					cur_row++;
					left -= 2;

				} else if (cur_row == R) {

					array[0 * C + cur_col] = '.';
					array[1 * C + cur_col] = '.';
					cur_col++;
					left -= 2;

				} else {

					if (alt) {
						array[0 * C + cur_col] = '.';
						array[1 * C + cur_col] = '.';
						cur_col++;
					} else {
						array[cur_row * C + 0] = '.';
						array[cur_row * C + 1] = '.';
						cur_row++;
					}
					left -= 2;
					alt = !alt;

				}
			}


			if (left < 2) {

				if (left == 0) {
					array[0] = 'c';
					return array, true, transpose;
				} else {

					if (cur_col > 2 && cur_row > 2) {
						array[2 * C + 2] = '.';
						array[0] = 'c';
						return array, true, transpose;
					} else {
						// impossible
						return nil, false, transpose;
					}

				}

			} else {


				for i := 0; i < left; i++ {

					y := 2 + i / (C - 2);
					x := 2 + i % (C - 2);
					array[y * C + x] = '.';

				}
				array[0] = 'c';
				return array, true, transpose;

			}


		}


	}



}

func main() {
	var test_count int;
	fmt.Scan(&test_count);

	for i := 0; i < test_count; i++ {

		var R, C, M int;

		fmt.Scan(&R, &C, &M);

		array, possible, transpose := minesweeper(R, C, M);

		// if !possible {
		// 	fmt.Println(i + 1);
		// }
		// continue;

		fmt.Printf("Case #%d:\n", i + 1);

		if (possible) {

			if (transpose) {

				for j := 0; j < R; j++ {
					for k := 0; k < C; k++ {
						fmt.Printf("%c", array[k * R + j]);
					}
					fmt.Println();
				}
			} else {
				for j := 0; j < R; j++ {
					for k := 0; k < C; k++ {
						fmt.Printf("%c", array[j * C + k]);
					}
					fmt.Println();
				}
			}

		} else {
			fmt.Printf("Impossible\n");
		}

	}

}
