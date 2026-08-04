// Sample grader for "Catfish Farm" (IOI 2022).
//
// Compile it together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < fish_sample.in
//
// The input format is
//     line 1:     N M
//     line 2 + i: X[i] Y[i] W[i]   (0 <= i <= M-1)
// and the grader prints the return value of max_weights.
//
// This is the same grader the judge compiles your submission with.
#include "fish.h"

#include <cstdio>
#include <vector>

int main() {
  int N, M;
  if (scanf("%d %d", &N, &M) != 2) return 0;
  std::vector<int> X(M), Y(M), W(M);
  for (int i = 0; i < M; ++i) {
    if (scanf("%d %d %d", &X[i], &Y[i], &W[i]) != 3) return 0;
  }
  printf("%lld\n", max_weights(N, M, X, Y, W));
  return 0;
}
