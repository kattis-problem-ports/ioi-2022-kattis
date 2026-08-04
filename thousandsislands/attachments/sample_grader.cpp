// Sample grader for "Thousands Islands" (IOI 2022).
//
// Compile it together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < islands_sample.in
//
// The input format is
//     line 1:     N M
//     line 2 + i: U[i] V[i]         (0 <= i <= M-1)
// and the grader prints
//     0 followed by 0 or 1, if find_journey returned a bool, or
//     1, then k, then c[0] ... c[k-1], if it returned an array.
// It does not check the journey; the judge does.
//
// This is the same grader the judge compiles your submission with.
#include "islands.h"

#include <cstdio>
#include <variant>
#include <vector>

int main() {
  int N, M;
  if (scanf("%d %d", &N, &M) != 2) return 0;
  std::vector<int> U(M), V(M);
  for (int i = 0; i < M; ++i) {
    if (scanf("%d %d", &U[i], &V[i]) != 2) return 0;
  }

  std::variant<bool, std::vector<int>> result = find_journey(N, M, U, V);
  if (result.index() == 0) {
    printf("0\n%d\n", std::get<bool>(result) ? 1 : 0);
  } else {
    const std::vector<int> &c = std::get<std::vector<int>>(result);
    printf("1\n%d\n", static_cast<int>(c.size()));
    for (size_t i = 0; i < c.size(); ++i) {
      printf("%d%c", c[i], i + 1 == c.size() ? '\n' : ' ');
    }
    if (c.empty()) printf("\n");
  }
  return 0;
}
