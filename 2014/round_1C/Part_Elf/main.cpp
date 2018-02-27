#include <iostream>
#include <cstdint>

int64_t test_rec(int64_t P, int64_t lQ) {

    if (P == 1LL) return lQ;

    return test_rec(P / 2, lQ - 1);

}

int64_t euclide(int64_t P, int64_t Q) {
    if (Q == 0) return P;
    return euclide(Q, P % Q);
}

void test(int t) {
    int64_t P, Q;
    char c;
    std::cin >> P;
    std::cin >> c;
    std::cin >> Q;

    int64_t R = euclide(Q, P);
    std::cerr << R << std::endl;
    P /= R;
    Q /= R;

    int64_t l;
    for (l = 40; l >= 0; l--) {
	if (Q == (1LL << l)) {
	    break;
	}
    }

    if (l < 0) {
	std::printf("Case #%d: impossible\n", t + 1);
    } else {
	std::printf("Case #%d: %ld\n", t + 1, test_rec(P, l));
    }

}

int main() {

    int T;
    std::cin >> T;
    for (int t = 0; t < T; t++) {
	test(t);
    }

}
