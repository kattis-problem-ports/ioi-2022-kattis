// Grader for "Rarest Insects" (IOI 2022). It is compiled together with your
// submission and takes care of all communication with the machine; you only
// implement min_cardinality as described in the problem statement.
//
// The grader does not count calls itself -- the judge does, and it stops the run
// as soon as any of the three counts would exceed 40000.
#include "insects.h"

#include <cstdio>
#include <cstdlib>

void move_inside(int i) {
  printf("I %d\n", i);
  fflush(stdout);
}

void move_outside(int i) {
  printf("O %d\n", i);
  fflush(stdout);
}

int press_button() {
  printf("P\n");
  fflush(stdout);
  int result;
  // The judge closes the connection when it has already decided the verdict
  // (too many calls, or an invalid index). Exiting quietly keeps that verdict.
  if (scanf("%d", &result) != 1) exit(0);
  return result;
}

int main() {
  int N;
  if (scanf("%d", &N) != 1) return 0;
  printf("A %d\n", min_cardinality(N));
  fflush(stdout);
  return 0;
}
