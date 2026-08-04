// Grader for "Catfish Farm" (IOI 2022). It is compiled together with your
// submission and takes care of all reading and writing; you only implement
// max_weights as described in the problem statement.
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
