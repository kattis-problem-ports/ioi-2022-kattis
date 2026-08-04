// Grader for "Digital Circuit" (IOI 2022). It is compiled together with your
// submission and takes care of all communication with the judge; you only
// implement init and count_ways as described in the problem statement.
//
// The judge hands over one update at a time and waits for its answer before
// revealing the next one, so count_ways cannot look ahead.
#include "circuit.h"

#include <cstdio>
#include <vector>

int main() {
  int N, M, Q;
  if (scanf("%d %d %d", &N, &M, &Q) != 3) return 0;
  std::vector<int> P(N + M), A(M);
  for (int i = 0; i < N + M; ++i) {
    if (scanf("%d", &P[i]) != 1) return 0;
  }
  for (int j = 0; j < M; ++j) {
    if (scanf("%d", &A[j]) != 1) return 0;
  }
  init(N, M, P, A);
  for (int k = 0; k < Q; ++k) {
    int L, R;
    if (scanf("%d %d", &L, &R) != 2) return 0;
    printf("%d\n", count_ways(L, R));
    fflush(stdout);
  }
  return 0;
}
