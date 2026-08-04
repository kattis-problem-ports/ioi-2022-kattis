#include "validate.h"

// Output validator for IOI 2022 "islands" (Thousands Islands).
//
// The statement's scoring rules, per test case:
//   a valid journey exists  -> a valid journey scores full,
//                              claiming existence without producing a valid
//                              journey (or producing more than 2*10^6 sailings)
//                              scores 35%, claiming non-existence scores 0;
//   no valid journey exists -> claiming non-existence scores full, anything
//                              else scores 0.
// The 35% is delivered through accept_with_score, which the patched
// data/gen.sh turns into a multiplier on the test group's score.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MAX_SAILINGS = 2000000;  // 2 * 10^6

static int N, M;
static vector<int> U, V;

// Precondition: every element of c is a valid canoe index.
static bool is_valid_journey(const vector<int>& c) {
    if (c.empty()) return false;  // must visit an island other than 0
    vector<int> u = U, v = V;
    vector<ll> used(M, 0);
    int cur = 0, prev = -1;
    for (int x : c) {
        if (x == prev) return false;  // same canoe twice in a row
        prev = x;
        if (u[x] != cur) return false;  // canoe is not docked here
        cur = v[x];
        used[x]++;
        swap(u[x], v[x]);
    }
    if (cur != 0) return false;
    for (int i = 0; i < M; i++)
        if (used[i] % 2 != 0) return false;  // canoe not back where it started
    return true;
}

// The score handed to accept_with_score is a fraction of the test group's
// score, which the patched data/gen.sh turns into a multiplier: the group
// grader multiplies it by the group's point value and does not round, so 35%
// of a 21-point group really is 7.35.
[[noreturn]] static void accept_fraction(double s) { accept_with_score(s); }

// 0 = claims no valid journey exists
// 1 = claims one exists but did not produce a valid one
// 2 = produced a valid journey
static int read_claim(istream& sol, feedback_function feedback) {
    ll type;
    if (!(sol >> type)) feedback("Expected more output");
    if (type != 0 && type != 1) feedback("First value is not 0 or 1");

    if (type == 0) {
        ll r;
        if (!(sol >> r)) feedback("Expected more output");
        if (r != 0 && r != 1) feedback("Second value is not 0 or 1");
        string trailing;
        if (sol >> trailing) feedback("Trailing output");
        return (int)r;
    }

    ll k;
    if (!(sol >> k)) feedback("Expected more output");
    if (k < 0) feedback("Number of sailings is negative");
    // More than 2*10^6 sailings only earns the partial score, so there is no
    // need to read (and no bound on) what follows.
    if (k > MAX_SAILINGS) return 1;

    vector<int> c;
    c.reserve((size_t)k);
    bool bad_index = false;
    for (ll i = 0; i < k; i++) {
        ll x;
        if (!(sol >> x)) feedback("Expected more output");
        if (x < 0 || x >= M) bad_index = true;  // an invalid journey, not a format error
        c.push_back(bad_index ? 0 : (int)x);
    }
    string trailing;
    if (sol >> trailing) feedback("Trailing output");
    if (bad_index) return 1;
    return is_valid_journey(c) ? 2 : 1;
}

int main(int argc, char** argv) {
    init_io(argc, argv);

    judge_in >> N >> M;
    U.resize(M);
    V.resize(M);
    for (int i = 0; i < M; i++) judge_in >> U[i] >> V[i];

    int judge = read_claim(judge_ans, judge_error);
    if (judge == 1)
        judge_error("Judge answer claims a journey exists but does not give a valid one");

    int sub = read_claim(author_out, wrong_answer);

    if (judge == 0) {
        if (sub == 2)
            judge_error("Submission found a valid journey, but judge says none exists");
        if (sub == 1) wrong_answer("Claimed that a valid journey exists, but none does");
        accept_fraction(1.0);
    }

    // A valid journey exists.
    if (sub == 0) wrong_answer("Claimed that no valid journey exists, but one does");
    if (sub == 1) {
        judge_message("No valid journey produced, but existence claimed: partial score\n");
        accept_fraction(0.35);
    }
    accept_fraction(1.0);
}
