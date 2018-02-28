#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>

#define MAX_N 12

char working[(1 << MAX_N) + 1];

#define WINNER_IF(a, b) \
  if ((x == a && y == b) || (x == b && y == a)) return a;
  
char winner(char x, char y) {
  WINNER_IF('P', 'R');
  WINNER_IF('R', 'S');
  WINNER_IF('S', 'P');
  return 0;
}

void rec(char *possibility, int size, int R, int P, int S) {

  if (R == 0 && P == 0 && S == 0) {
    char test[1 << MAX_N];
    std::memcpy(test, possibility, size * sizeof(char));

    for (int n = size; n >= 1; n /= 2) {
      for (int i = 0; i < n / 2; i++) {
	char w = winner(test[2 * i], test[2 * i + 1]);
	if (w == 0) return;
	test[i] = w;
      }
    }

    int i = 0;
    while (possibility[i] == working[i]) {
      i++;
    }

    if (possibility[i] < working[i]) {
      std::memcpy(working, possibility, size * sizeof(char));
    }

    return;

  }
  
  if (R > 0) {
    possibility[size] = 'R';
    rec(possibility, size + 1, R - 1, P, S);
  }

  if (P > 0) {
    possibility[size] = 'P';
    rec(possibility, size + 1, R, P - 1, S);
  }

  if (S > 0) {
    possibility[size] = 'S';
    rec(possibility, size + 1, R, P, S - 1);
  }
  
}

void test(int t) {

  int N, R, P, S;
  scanf("%d", &N);
  scanf("%d", &R);
  scanf("%d", &P);
  scanf("%d", &S);
  
  char possibility[(1 << MAX_N) + 1];
  working[0] = 'T';
  rec(possibility, 0, R, P, S);

  if (working[0] == 'T') {
    printf("Case #%d: IMPOSSIBLE\n", t + 1);
  } else {
    working[P + R + S] = 0;
    printf("Case #%d: %s\n", t + 1, working);
  }
  
}

struct char2 {
  char c[2];
};

void expand(char initial, char combination[(1 << MAX_N) + 1], int N) {

  std::map<char, char2> m;
  m['P'].c[0] = 'P';
  m['P'].c[1] = 'R';

  m['S'].c[0] = 'P';
  m['S'].c[1] = 'S';

  m['R'].c[0] = 'R';
  m['R'].c[1] = 'S';

  char old_combination[1 << MAX_N];
  char new_combination[1 << MAX_N];

  old_combination[0] = initial;
  for (int n = 0; n < N; n++) {
    for (int i = 0; i < (1 << n); i++) {
      new_combination[2 * i + 0] = m[old_combination[i]].c[0];
      new_combination[2 * i + 1] = m[old_combination[i]].c[1];
    }

    std::swap(new_combination, old_combination);
    
  }

  std::memcpy(combination, old_combination, sizeof(old_combination));

}

bool is_valid(char combination[(1 << MAX_N) + 1], int N, int R, int P, int S) {
  for (int i = 0; i < (1 << N); i++) {
    if (combination[i] == 'R') R--;
    if (combination[i] == 'P') P--;
    if (combination[i] == 'S') S--;
  }

  return (R == 0 && S == 0 && P == 0);
}

void sort_tree(char *combination, int N) {

  if (N == 0) return;
  
  sort_tree(combination, N - 1);
  sort_tree(combination + (1 << (N - 1)), N - 1);

  int i = 0;
  while (combination[i] == combination[(1 << (N - 1)) + i]) i++;
  
  if (combination[i] > combination[(1 << (N - 1)) + i]) {
    
    for (int i = 0; i < (1 << (N - 1)); i++) {
      std::swap(combination[i], combination[(1 << (N - 1)) + i]);
    }
    
  }
  
}


void test2(int t) {

  int N, R, P, S;
  scanf("%d", &N);
  scanf("%d", &R);
  scanf("%d", &P);
  scanf("%d", &S);

  char combination1[(1 << MAX_N) + 1];
  char combination2[(1 << MAX_N) + 1];
  char combination3[(1 << MAX_N) + 1];

  expand('P', combination1, N);
  expand('S', combination2, N);
  expand('R', combination3, N);

  sort_tree(combination1, N);
  sort_tree(combination2, N);
  sort_tree(combination3, N);

  char *best_combination = NULL;
  
  if (is_valid(combination1, N, R, P, S)) {
    best_combination = combination1;
  }

  if (is_valid(combination2, N, R, P, S)) {
    if (best_combination == NULL) {
      best_combination = combination2;
    } else {
      int i = 0;
      while (combination2[i] == best_combination[i]) i++;
      if (combination2[i] < best_combination[i]) {
	best_combination = combination2;
      }
    }
  }


  if (is_valid(combination3, N, R, P, S)) {
    if (best_combination == NULL) {
      best_combination = combination3;
    } else {
      int i = 0;
      while (combination3[i] == best_combination[i]) i++;
      if (combination3[i] < best_combination[i]) {
	best_combination = combination3;
      }
    }
  }

  if (best_combination) {
    best_combination[(1 << N)] = 0;
    printf("Case #%d: %s\n", t + 1, best_combination);
  } else {
    printf("Case #%d: IMPOSSIBLE\n", t + 1);
  }
  
}


int main() {

  int T;
  scanf("%d", &T);
  
  for (int t = 0; t < T; t++) {
    test2(t);
  }
  
  return 0;
}
