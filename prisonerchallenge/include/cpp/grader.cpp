// Grader for "Prisoner Challenge" (IOI 2022). It is compiled together with your
// submission and takes care of all reading and writing; you only implement
// devise_strategy as described in the problem statement.
#include "prison.h"

#include <cstdio>
#include <vector>

int main() {
  int N;
  if (scanf("%d", &N) != 1) return 0;
  std::vector<std::vector<int>> s = devise_strategy(N);

  // A return value that is not an (x+1) x (N+1) table cannot be printed in the
  // format the judge expects. Emit x = -1, which the judge rejects, so that a
  // malformed strategy is a wrong answer rather than a crash or a truncated
  // table that might parse as a different strategy.
  int x = static_cast<int>(s.size()) - 1;
  bool ok = x >= 0;
  for (const std::vector<int> &row : s) {
    if (static_cast<int>(row.size()) != N + 1) ok = false;
  }
  if (!ok) {
    printf("-1\n");
    return 0;
  }

  printf("%d\n", x);
  for (const std::vector<int> &row : s) {
    for (size_t j = 0; j < row.size(); ++j) {
      printf("%d%c", row[j], j + 1 == row.size() ? '\n' : ' ');
    }
  }
  return 0;
}
