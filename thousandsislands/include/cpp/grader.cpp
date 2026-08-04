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
    std::vector<int> &c = std::get<std::vector<int>>(result);
    // An array of more than 2*10^6 integers earns the partial score whatever it
    // contains, so the official grader replaced it with an empty array instead
    // of printing it (in a SECRET block, which is why the attachment does not
    // have this). Keeping it here bounds the output at 2*10^6 indices: the judge
    // sees an array that does not describe a valid journey either way, and a
    // submission cannot lose the partial score to an output-limit failure.
    if (c.size() > 2000000) c.clear();
    printf("1\n%d\n", static_cast<int>(c.size()));
    for (size_t i = 0; i < c.size(); ++i) {
      printf("%d%c", c[i], i + 1 == c.size() ? '\n' : ' ');
    }
    if (c.empty()) printf("\n");
  }
  return 0;
}
