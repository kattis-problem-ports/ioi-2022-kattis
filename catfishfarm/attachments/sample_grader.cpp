// Sample grader for "Catfish Farm" (IOI 2022).
//
// This is the official IOI 2022 sample grader, copied verbatim. Compile it
// together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < fish_sample.in
//
// It reads N and M, then the M catfish, and prints the return value of
// max_weights. See the Sample Grader section of the statement.
#include "fish.h"

#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> X(M), Y(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &X[i], &Y[i], &W[i]));
  }

  long long result = max_weights(N, M, X, Y, W);
  printf("%lld\n", result);
  return 0;
}
