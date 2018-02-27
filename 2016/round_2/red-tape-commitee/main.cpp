#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MAX_N 200


void add_prob(double *probabilities1, double *probabilities2, double p, int K) {
  probabilities2[0] = probabilities1[0] * (1.0 - p);
  for (int k = 1; k < K; k++) {
    probabilities2[k] = probabilities1[k - 1] * p + probabilities1[k] * (1.0 - p);
  }
  probabilities2[K] = probabilities1[K - 1] * p;

}

void test(int t) {
  int K, N;
  scanf("%d", &N);
  scanf("%d", &K);

  double data[MAX_N];

  for (int n = 0; n < N; n++) {
    scanf("%lf", data + n);
  }

  double probabilities[MAX_N];
  double temp_probabilities[MAX_N];

  std::sort(data, data + N);

  probabilities[0] = 1.0f;

  for (int k = 0; k < K / 2; k++) {
    add_prob(probabilities, temp_probabilities, data[k]        , 2 * k + 1);
    add_prob(temp_probabilities, probabilities, data[N - k - 1], 2 * k + 2);
  }

  printf("Case #%d: %lf\n", t + 1, probabilities[K / 2]);
  // for (int i = 0; i < K + 1; i++) {
  //   printf("%d : %f\n", i, probabilities[i]);
  // }


}

double best_proba;

void rec(double *data, double *probabilities, int i, int N, int k, int K) {

  if (k == K) {
    if (probabilities[K / 2] > best_proba) {
      best_proba = probabilities[K / 2];
      printf("best_proba : %lf\n", best_proba);
    }
    return;
  }

  if (N - i < K - k) {
    return;
  }

  double temp_probabilities[MAX_N];
  add_prob(probabilities, temp_probabilities, data[i], k + 1);
  printf("%d : 1\n", i);
  rec(data, temp_probabilities, i + 1, N, k + 1, K);

  std::memcpy(temp_probabilities, probabilities, (k + 1) * sizeof(double));
  printf("%d : 0\n", i);
  rec(data, temp_probabilities, i + 1, N, k, K);

}

void test_rec(int t) {
  int K, N;
  scanf("%d", &N);
  scanf("%d", &K);

  double data[MAX_N];

  for (int n = 0; n < N; n++) {
    scanf("%lf", data + n);
  }

  double probabilities[MAX_N];

  probabilities[0] = 1.0f;

  best_proba = 0.0f;
  rec(data, probabilities, 0, N, 0, K);


  printf("Case #%d: %lf\n", t + 1, best_proba);
  // for (int i = 0; i < K + 1; i++) {
  //   printf("%d : %f\n", i, probabilities[i]);
  // }

}


int main() {

  int T;
  scanf("%d", &T);

  for (int t = 0; t < T; t++) {
    test(t);
  }

  return 0;
}
