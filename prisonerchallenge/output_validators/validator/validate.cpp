#include "validate.h"

// Output validator for IOI 2022 "prison" (Prisoner Challenge).
//
// The submission prints a strategy: x on the first line, then x+1 lines of
// N+1 integers. The validator
//   * rejects x above the group's limit (flag maxx),
//   * simulates the strategy on every ordered pair (A, B) with A != B and
//     rejects it if the prisoners ever lose,
//   * with the flag "partial", scores the run by the statement's table for
//     test group 3 (a fraction of the group score, delivered through
//     accept_with_score, which the patched data/gen.sh turns into a
//     multiplier).
//
// The judge answer is checked with exactly the same routine.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_PRISONERS = 500;

static int N;
static ll maxx;
static bool partial_scoring;

struct Strategy {
    int x = 0;
    // row-major (x+1) x (N+1)
    vector<int> s;
    int at(int i, int j) const { return s[(size_t)i * (N + 1) + j]; }
};

// Reads a strategy. Any deviation from the format, or an x above the group's
// limit, is reported through `feedback`.
static void read_strategy(istream& in, feedback_function feedback, Strategy& st) {
    ll x;
    if (!(in >> x)) feedback("Expected more output");
    if (x < 0) feedback("x is negative");
    if (x > maxx) feedback("x is larger than this test group allows");
    st.x = (int)x;
    st.s.assign((size_t)(st.x + 1) * (N + 1), 0);
    for (int i = 0; i <= st.x; i++) {
        for (int j = 0; j <= N; j++) {
            ll v;
            if (!(in >> v)) feedback("Expected more output");
            if (j == 0) {
                if (v != 0 && v != 1) feedback("s[i][0] is neither 0 nor 1");
            } else if (v < -2 || v > x) {
                feedback("s[i][j] is outside [-2, x]");
            }
            st.s[(size_t)i * (N + 1) + j] = (int)v;
        }
    }
    string trailing;
    if (in >> trailing) feedback("Trailing output");
}

// Runs the challenge for one arrangement of the bags. Returns true if the
// prisoners win.
static bool simulate(const Strategy& st, int A, int B) {
    const int expected = A < B ? -1 : -2;
    int whiteboard = 0;
    for (int step = 0; step < MAX_PRISONERS; step++) {
        int bag = st.at(whiteboard, 0);
        whiteboard = st.at(whiteboard, bag == 0 ? A : B);
        if (whiteboard < 0) return whiteboard == expected;
    }
    return false;  // all 500 prisoners entered without identifying a bag
}

// Reports through `feedback` if the strategy ever loses.
static void check_strategy(const Strategy& st, feedback_function feedback) {
    for (int A = 1; A <= N; A++) {
        for (int B = 1; B <= N; B++) {
            if (A == B) continue;
            if (!simulate(st, A, B)) {
                // The pair is derived from the input only, so naming it leaks
                // nothing that the submission does not already know.
                feedback("Strategy fails for A = %d, B = %d", A, B);
            }
        }
    }
}

// Points awarded for a given x in test group 3, out of the group's 90.
static double group3_fraction(int x) {
    double score;
    if (x <= 20) score = 90;
    else if (x == 21) score = 80;
    else if (x == 22) score = 70;
    else if (x == 23) score = 62;
    else if (x == 24) score = 55;
    else if (x == 25) score = 50;
    else if (x <= 39) score = 25 + 1.5 * (40 - x);
    else score = 20;  // 40 <= x <= 60; larger x was already rejected
    return score / 90.0;
}

// The score handed to accept_with_score is a fraction of the test group's
// score, which the patched data/gen.sh turns into a multiplier: the group
// grader multiplies it by the group's point value and does not round, so the
// fractions below come out as the statement's exact point values.
[[noreturn]] static void accept_fraction(double s) { accept_with_score(s); }

int main(int argc, char** argv) {
    init_io(argc, argv);

    maxx = MAX_PRISONERS;
    partial_scoring = false;
    for (int i = 4; i < argc; i++) {
        string a = argv[i];
        if (a.rfind("maxx=", 0) == 0) maxx = atoll(a.c_str() + 5);
        else if (a == "partial") partial_scoring = true;
    }

    judge_in >> N;

    Strategy judge, sub;
    read_strategy(judge_ans, judge_error, judge);
    check_strategy(judge, judge_error);

    read_strategy(author_out, wrong_answer, sub);
    check_strategy(sub, wrong_answer);

    if (!partial_scoring) accept_fraction(1.0);

    judge_message("x = %d\n", sub.x);
    accept_fraction(group3_fraction(sub.x));
}
