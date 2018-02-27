#include <cstdio>
#include <vector>
#include <cstring>

#define J_MAX 3
#define P_MAX 3
#define S_MAX 3

#define K_MAX 10

struct possibility {
  int j;
  int p;
  int s;
};

bool best_taken[S_MAX * J_MAX * P_MAX];
int best_count = 0;

void rec(possibility *possibilities, bool *taken, int possibilities_size, int K, int id, int count) {

  if (id == possibilities_size) {
    if (count > best_count) {
      best_count = count;
      std::memcpy(best_taken, taken, possibilities_size * sizeof(bool));
    }
    return;
  }

  if (count + possibilities_size - id <  best_count) {
    return;
  }

  int k_jp = 0;
  int k_js = 0;
  int k_ps = 0;
  
  for (int i = 0; i < id; i++) {
    if (taken[i]) {
      if (possibilities[i].j == possibilities[id].j &&
	  possibilities[i].p == possibilities[id].p) {
	k_jp++;
      }

      if (possibilities[i].j == possibilities[id].j &&
	  possibilities[i].s == possibilities[id].s) {
	k_js++;
      }

      if (possibilities[i].p == possibilities[id].p &&
	  possibilities[i].s == possibilities[id].s) {
	k_ps++;
      }
    }
  }

  if (k_jp == K && k_js == K && k_ps == K) {
    std::memset(taken + id, 0, sizeof(bool) * possibilities_size - id);
    rec(possibilities, taken, possibilities_size, K, possibilities_size, count);
    return;
  }

  if (k_jp < K && k_js < K && k_ps < K) {
    taken[id] = true;
    rec(possibilities, taken, possibilities_size, K, id + 1, count + 1);
  }

  taken[id] = false;
  rec(possibilities, taken, possibilities_size, K, id + 1, count);  
  
}

void test(int t) {

  int J, P, S, K;
  
  scanf("%d", &J);
  scanf("%d", &P);
  scanf("%d", &S);
  scanf("%d", &K);

  best_count = 0;

  possibility possibilities[J_MAX * P_MAX * S_MAX];
  bool taken[J_MAX * P_MAX * S_MAX] = {};

  int id = 0;
  for (int j = 0; j < J; j++) {
    for (int p = 0; p < P; p++) {
      for (int s = 0; s < S; s++) {
	possibilities[id].j = j;
	possibilities[id].p = p;
	possibilities[id].s = s;
	taken[id] = false;
	id++;
      }
    }
  }

  rec(possibilities, taken, J * P * S, K, 0, 0);


  printf("Case #%d: %d\n", t + 1, best_count);
  for (int i = 0; i < J * P * S; i++) {
    if (best_taken[i]) {
      printf("%d %d %d\n", possibilities[i].j + 1, possibilities[i].p + 1, possibilities[i].s + 1);
    }
  }
  
}

struct pair {
  int x;
  int y;
};

struct triplet {
  int x;
  int y;
  int z;
};

// void test2(int t) {

//   int J, P, S, K;
  
//   scanf("%d", &J);
//   scanf("%d", &P);
//   scanf("%d", &S);
//   scanf("%d", &K);

//   int jp = 0;
//   int js = 0;
//   int ps = 0;
  
//   int set3_size = 0;
//   triplet set3[J_MAX * P_MAX * S_MAX];
//   for (int j = 0; j < J; j++) {
//     for (int p = 0; p < P; p++) {
//       for (int s = 0; s < S; s++) {

// 	int k_jp = 0;
// 	int k_js = 0;
// 	int k_ps = 0;
	
// 	for (int i = 0; i < set3_size; i++) {
// 	    if (set3[i].x == j && set3[i].y == p) {
// 	      k_jp++;
// 	    }

// 	    if (set3[i].x == j && set3[i].z == s) {
// 	      k_js++;
// 	    }

// 	    if (set3[i].y == p && set3[i].z == s) {
// 	      k_ps++;
// 	    }
// 	}

// 	if (k_jp < K &&  k_js < K && k_ps < K) {
// 	  set3[set3_size].x = j;
// 	  set3[set3_size].y = p;
// 	  set3[set3_size].z = s;
// 	  set3_size++;
// 	}

	
//       }
//     }
//   }

//   printf("Case #%d: %d\n", t + 1, set3_size);
//   for (int i = 0; i < set3_size; i++) {
//     printf("%d %d %d\n", set3[i].x + 1, set3[i].y + 1, set3[i].z + 1);
//   }
  
// }

int main() {

  int T;
  scanf("%d", &T);

  for (int t = 0; t < T; t++) {
    test(t);
  }

  
  return 0;
}
