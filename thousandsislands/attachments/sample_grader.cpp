// Sample grader for "Thousands Islands" (IOI 2022).
//
// This is the official IOI 2022 sample grader, copied verbatim. Compile it
// together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < islands_sample.in
//
// It reads N and M, then the M canoes, and prints what find_journey
// returned. It does not check whether the journey is valid; the judge does.
// See the Sample Grader section of the statement.
#include "islands.h"

#include <cassert>
#include <cstdio>

#include <variant>
#include <vector>

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));

  std::vector<int> U(M), V(M);
  for (int i = 0; i < M; ++i) {
    assert(2 == scanf("%d %d", &U[i], &V[i]));
  }

  std::variant<bool, std::vector<int>> result = find_journey(N, M, U, V);
  if (result.index() == 0) {
    printf("0\n");
    if (std::get<bool>(result)) {
      printf("1\n");
    } else {
      printf("0\n");
    }
  } else {
    printf("1\n");
    std::vector<int> &canoes = std::get<std::vector<int>>(result);
    printf("%d\n", static_cast<int>(canoes.size()));
    for (int i = 0; i < static_cast<int>(canoes.size()); ++i) {
      if (i > 0) {
        printf(" ");
      }
      printf("%d", canoes[i]);
    }
    printf("\n");
  }
  return 0;
}
