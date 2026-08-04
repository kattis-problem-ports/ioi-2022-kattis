// Sample grader for "Radio Towers" (IOI 2022).
//
// Compile it together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < towers_sample.in
//
// The input format is
//     line 1:     N Q
//     line 2:     H[0] H[1] ... H[N-1]
//     line 3 + j: L R D             (question j, 0 <= j <= Q-1)
// and the grader prints the Q return values of max_towers, one per line.
//
// This is the same grader the judge compiles your submission with. Reading a
// file, it has every question available from the start; the judge instead sends
// them one at a time, which makes no difference to your solution.
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
