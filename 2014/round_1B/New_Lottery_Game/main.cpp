#include <iostream>
#include <cmath>
#include <cstdint>

void test_naive(int t) {

    int A, B, K;
    std::cin >> A;
    std::cin >> B;
    std::cin >> K;

    int count = 0;
    for (int i = 0; i < A; i++) {
	for (int j = 0; j < B; j++) {
	    if ((i & j) < K) {
		// std::printf("%d - %d\n", i, j);
		count++;
	    }
	}
    }

    std::printf("Case (naive) #%d: %d", t + 1, count);
    std::printf("\n");
}

int64_t test_rec(unsigned int A, unsigned int B, unsigned int K) {

    if (K >= A || K >= B) {
	return ((int64_t) (A + 1)) * ((int64_t) (B + 1));
    }

    int i = 31;
    while (!((A & (1 << i)) || (B & (1 << i)))) i--;

    int b1 = (A & (1 << i));
    int b2 = (B & (1 << i));
    int b3 = (K & (1 << i));


    int64_t result = 0;
    if (!b1 && !b2) {
	// Not possible
    } else if (!b1 && b2) {
	if (b3) {
	    result += test_rec(A, (1 << i) - 1, (1 << i) - 1);
	    result += test_rec(A, B ^ b2, (1 << i) - 1);
	} else {
	    result += test_rec(A, (1 << i) - 1, K);
	    result += test_rec(A, B ^ b2, K);
	}

    } else if (b1 && !b2) {
	if (b3) {
	    result += test_rec((1 << i) - 1, B, (1 << i) - 1);
	    result += test_rec(A ^ b1, B, (1 << i) - 1);
	} else {
	    result += test_rec((1 << i) - 1, B, K);
	    result += test_rec(A ^ b1, B, K);
	}

    } else if (b1 && b2) {

	if (b3) {
	    result += test_rec((1 << i) - 1, (1 << i) - 1, (1 << i) - 1);
	    result += test_rec((1 << i) - 1, B ^ b2, (1 << i) - 1);
	    result += test_rec(A ^ b1, (1 << i) - 1, (1 << i) - 1);
	    result += test_rec(A ^ b1, B ^ b2, K ^ b3);
	} else  {
	    result += test_rec((1 << i) - 1, (1 << i) - 1, K);
	    result += test_rec((1 << i) - 1, B ^ b2, K);
	    result += test_rec(A ^ b1, (1 << i) - 1, K);
	}

    }

    return result;


}

void test2(int t) {
    unsigned int A, B, K;
    std::cin >> A;
    std::cin >> B;
    std::cin >> K;

    int64_t count = test_rec(A - 1, B - 1, K - 1);

    std::printf("Case #%d: %ld", t + 1, count);
    std::printf("\n");
}

void test(int t) {

    unsigned int A, B, K;
    std::cin >> A;
    std::cin >> B;
    std::cin >> K;


    int res = 1;
    int k = 0;
    for (; (1 << k) <= (K - 1); k++) {
	if ((1 << k) & (K - 1)) {
	    res += 3 * (1 << (2*k));
	} else {
	    res *= 3;
	}
    }


    int64_t count = 0;
    for (int i = 31; i >= 0; i--) {
	if (A & (1 << i)) {
	    for (int j = 31; j >= 0; j--) {
		if (B & (1 << j)) {
		    int min = std::min(i, j);
		    int max = std::max(i, j);
		    if ((1 << min) < K) {
			count += ((1 << min) - 1) * ((1 << max) - 1);
		    } else {
			count += res * std::pow(3, min - k) * std::pow(2, max - min);
		    }
		}
	    }
	}
    }


    std::printf("Case #%d: %ld", t + 1, count);
    std::printf("\n");
}


int main(int argc, char **argv) {

    bool naive = false;
    if (argc > 1) {
	naive = true;
    }

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	if (naive) {
	test_naive(t);
	} else {
	test2(t);
	}
    }


    return 0;
}
