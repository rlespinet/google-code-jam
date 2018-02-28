package main;

import (
	"fmt"
)

func main() {
	var test_count int;
	fmt.Scan(&test_count);

	for i := 0; i < test_count; i++ {

		var r1_id, r2_id int;
		fmt.Scan(&r1_id);

		var r1, r2 [4]int;

		for j := 0; j < 4; j++ {
			var t0, t1, t2, t3 int;
			fmt.Scan(&t0, &t1, &t2, &t3);
			if (r1_id == j + 1) {
				r1[0] = t0;
				r1[1] = t1;
				r1[2] = t2;
				r1[3] = t3;
			}
		}

		fmt.Scan(&r2_id);

		for j := 0; j < 4; j++ {
			var t0, t1, t2, t3 int;
			fmt.Scan(&t0, &t1, &t2, &t3);
			if (r2_id == j + 1) {
				r2[0] = t0;
				r2[1] = t1;
				r2[2] = t2;
				r2[3] = t3;
			}
		}

		answer_count := 0;
		answer := 0;
		for j := 0; j < 4; j++ {
			for k := 0; k < 4; k++ {
				if r1[j] == r2[k] {
					answer_count++;
					answer = r1[j];
				}
			}
		}


		fmt.Printf("Case #%d: ", i + 1);
		if (answer_count == 0) {
			fmt.Printf("Volunteer cheated!\n");
		} else if (answer_count == 1) {
			fmt.Printf("%d\n", answer);
		} else {
			fmt.Printf("Bad magician!\n");
		}

	}

}
