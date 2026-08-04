// Grader for "Thousands Islands" (IOI 2022). It is compiled together with your
// submission and takes care of all reading and writing; you only implement
// find_journey as described in the problem statement.
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
