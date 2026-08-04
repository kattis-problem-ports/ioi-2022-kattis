// Sample grader for "Digital Circuit" (IOI 2022).
//
// Compile it together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < circuit_sample.in
//
// The input format is
//     line 1:     N M Q
//     line 2:     P[0] P[1] ... P[N+M-1]
//     line 3:     A[0] A[1] ... A[M-1]
//     line 4 + k: L R               (update k, 0 <= k <= Q-1)
// and the grader prints the Q return values of count_ways, one per line.
//
// This is the same grader the judge compiles your submission with. Reading a
// file, it has every update available from the start; the judge instead sends
// them one at a time, which makes no difference to your solution.
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
