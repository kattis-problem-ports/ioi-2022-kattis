// Sample grader for "Rarest Insects" (IOI 2022).
//
// Compile it together with your own solution, for example
//     g++ -O2 -std=gnu++20 -o solution sample_grader.cpp solution.cpp
// and run it on an input file:
//     ./solution < insects_sample.in
//
// The input format is
//     line 1: N
//     line 2: T[0] T[1] ... T[N-1]
// where T[i] is the type of insect i. The grader prints the return value of
// min_cardinality on the first line and q -- the largest of the three call
// counts -- on the second. If your solution breaks the rules it prints
// "Protocol Violation: <MSG>" instead, where <MSG> is "invalid parameter" or
// "too many calls".
//
// This grader runs the machine inside your own process. The judge runs it as a
// separate program, and its verdict is the one that counts.
#include "insects.h"

#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>

static const int MAX_CALLS = 40000;

static int n;
static std::vector<int> colour;   // insect -> compressed type
static std::vector<char> inside;
static std::vector<int> occ;      // compressed type -> how many are inside
static int calls[3];              // move_inside, move_outside, press_button

[[noreturn]] static void violation(const char *msg) {
  printf("Protocol Violation: %s\n", msg);
  exit(0);
}

static void count_call(int which) {
  if (++calls[which] > MAX_CALLS) violation("too many calls");
}

void move_inside(int i) {
  count_call(0);
  if (i < 0 || i >= n) violation("invalid parameter");
  if (!inside[i]) {
    inside[i] = 1;
    occ[colour[i]]++;
  }
}

void move_outside(int i) {
  count_call(1);
  if (i < 0 || i >= n) violation("invalid parameter");
  if (inside[i]) {
    inside[i] = 0;
    occ[colour[i]]--;
  }
}

int press_button() {
  count_call(2);
  int best = 0;
  for (int c : occ) {
    if (c > best) best = c;
  }
  return best;
}

int main() {
  if (scanf("%d", &n) != 1) return 1;
  std::map<int, int> ids;
  colour.assign(n, 0);
  for (int i = 0; i < n; ++i) {
    int t;
    if (scanf("%d", &t) != 1) return 1;
    std::map<int, int>::iterator it = ids.find(t);
    if (it == ids.end()) it = ids.emplace(t, static_cast<int>(ids.size())).first;
    colour[i] = it->second;
  }
  inside.assign(n, 0);
  occ.assign(ids.size(), 0);

  int answer = min_cardinality(n);

  int q = calls[0];
  if (calls[1] > q) q = calls[1];
  if (calls[2] > q) q = calls[2];
  printf("%d\n%d\n", answer, q);
  return 0;
}
