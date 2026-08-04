// Grader for "Radio Towers" (IOI 2022). It is compiled together with your
// submission and takes care of all communication with the judge; you only
// implement init and max_towers as described in the problem statement.
//
// The judge hands over one question at a time and waits for its answer before
// revealing the next one, so max_towers cannot look ahead.
#include "towers.h"

#include <cstdio>
#include <vector>

int main() {
  int N, Q;
  if (scanf("%d %d", &N, &Q) != 2) return 0;
  std::vector<int> H(N);
  for (int i = 0; i < N; ++i) {
    if (scanf("%d", &H[i]) != 1) return 0;
  }
  init(N, H);
  for (int j = 0; j < Q; ++j) {
    int L, R, D;
    if (scanf("%d %d %d", &L, &R, &D) != 3) return 0;
    printf("%d\n", max_towers(L, R, D));
    fflush(stdout);
  }
  return 0;
}
