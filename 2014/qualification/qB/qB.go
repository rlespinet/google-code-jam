package main;

import (
	"fmt"
)

func calculate_time(C float64, F float64, X float64) float64{
	CPS := 2.0;

	acc := 0.0;

	for {

		t1 := X / CPS;

		t2 := X / (CPS + F) + C / CPS;

		if (t1 < t2) {
			// Stop
			return t1 + acc;
		}

		acc += C / CPS;
		CPS += F;

	}

}

func main() {
	var test_count int;
	fmt.Scan(&test_count);

	for i := 0; i < test_count; i++ {

		var C, F, X float64;

		fmt.Scan(&C, &F, &X);

		result := calculate_time(C, F, X);

		fmt.Printf("Case #%d: %f\n", i + 1, result);

	}

}
