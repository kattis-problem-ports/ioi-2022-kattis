#include "validate.h"

// Interactive output validator for IOI 2022 "insects" (Rarest Insects).
//
// Judge input file:  N on the first line, then the N insect types.
// Judge answer file: the word "partial" if this case is scored by its operation
//   count (the original package's is_partial=1), anything else if it is not.
//   See data/generator.sh; the only case whose answer file is not one of the two
//   flags is the sample, which is is_partial=0 and reads correctly as "not
//   partial".
//
// Protocol (see the statement):
//   validator -> submission : N
//   submission -> validator : "I i" | "O i" | "P" | "A c"
//   validator -> submission : the answer to each "P"
//
// Each of "I", "O" and "P" may be used at most 40000 times. The run is scored by
// the statement's table for test group 3 -- using m = Q / N, where Q is the
// largest of the three operation counts -- when the group passes the "partial"
// flag *and* the case is flagged in the judge answer. Both are needed because
// is_partial was a property of the case rather than of the subtask: the original
// ran the file this port calls 1-01 unscored in subtasks 1, 2 and 3 and ran its
// byte-identical twin 3-01 scored in subtask 3, and deduplicating them leaves one
// file that group 3 must score and groups 1 and 2 must not. The fraction is
// delivered through accept_with_score, which the patched data/gen.sh turns into a
// multiplier on the group score.

#include <csignal>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

using ll = long long;

const ll MAX_OPS = 40000;

// Never echo anything the submission printed; only fixed reasons.
[[noreturn]] static void protocol_error(const char* why) {
    author_message("Protocol violation\n");
    wrong_answer("Protocol violation: %s\n", why);
}

// The score handed to accept_with_score is a fraction of the test group's
// score, which the patched data/gen.sh turns into a multiplier: the group
// grader multiplies it by the group's point value and does not round, so the
// statement's two-decimal points come through unchanged.
[[noreturn]] static void accept_fraction(double s) { accept_with_score(s); }

static double round_two_dp(double v) { return round(v * 100.0) / 100.0; }

// Points out of 75 for test group 3, as a function of m = Q / N.
static double group3_points(double m) {
    if (m <= 3.0) return 75.0;
    if (m <= 6.0) return round_two_dp(81.0 - m * m * 2.0 / 3.0);
    return round_two_dp(225.0 / (m - 2.0));  // 6 < m <= 20
}

int main(int argc, char** argv) {
    init_io(argc, argv);
    // If the submission dies early, keep running so a verdict can be reported.
    signal(SIGPIPE, SIG_IGN);

    bool partial_group = false;
    for (int i = 4; i < argc; i++)
        if (string(argv[i]) == "partial") partial_group = true;

    // The judge answer holds the original package's is_partial flag for this
    // case. It is a property of the case, not of the group, so the score table
    // needs both it and the group's flag; see the note at the top of the file.
    string case_flag;
    judge_ans >> case_flag;
    const bool partial_scoring = partial_group && case_flag == "partial";

    int n;
    if (!(judge_in >> n)) judge_error("could not read N from the judge input");

    vector<int> color(n);
    map<ll, int> type_id;
    for (int i = 0; i < n; i++) {
        ll t;
        if (!(judge_in >> t)) judge_error("could not read type %d", i);
        auto it = type_id.find(t);
        if (it == type_id.end()) it = type_id.emplace(t, (int)type_id.size()).first;
        color[i] = it->second;
    }
    const int kinds = (int)type_id.size();

    // The cardinality of the rarest type over all insects.
    vector<ll> total(kinds, 0);
    for (int i = 0; i < n; i++) total[color[i]]++;
    const ll rarest = *min_element(total.begin(), total.end());

    // Machine state: which insects are inside, the per-type counts inside, and a
    // multiset of those counts so that the maximum is cheap to read.
    vector<char> inside(n, 0);
    vector<ll> occ(kinds, 0);
    multiset<ll> occs;
    for (int i = 0; i < kinds; i++) occs.insert(0);

    ll ops[3] = {0, 0, 0};  // I, O, P

    printf("%d\n", n);
    fflush(stdout);

    string cmd;
    while (author_out >> cmd) {
        if (cmd == "I" || cmd == "O") {
            const int which = cmd == "I" ? 0 : 1;
            if (++ops[which] > MAX_OPS)
                protocol_error("too many operations of one kind");
            ll i;
            if (!(author_out >> i)) protocol_error("missing insect index");
            if (i < 0 || i >= n) protocol_error("insect index out of range");
            const char want = which == 0 ? 1 : 0;
            if (inside[i] != want) {
                inside[i] = want;
                const int c = color[i];
                occs.erase(occs.find(occ[c]));
                occ[c] += want ? 1 : -1;
                occs.insert(occ[c]);
            }
        } else if (cmd == "P") {
            if (++ops[2] > MAX_OPS)
                protocol_error("too many operations of one kind");
            printf("%lld\n", *occs.rbegin());
            fflush(stdout);
        } else if (cmd == "A") {
            ll answer;
            if (!(author_out >> answer)) protocol_error("missing answer");
            string trailing;
            if (author_out >> trailing) protocol_error("output after the answer");
            if (answer != rarest)
                wrong_answer("Answer is %lld, expected %lld\n", answer, rarest);

            const ll q = max(ops[0], max(ops[1], ops[2]));
            const double m = (double)q / (double)n;
            judge_message("N = %d, Q = %lld, Q/N = %.4f\n", n, q, m);
            if (!partial_scoring) accept_fraction(1.0);
            if (m > 20.0) wrong_answer("Q/N = %.4f exceeds 20\n", m);
            accept_fraction(group3_points(m) / 75.0);
        } else {
            protocol_error("unknown command");
        }
    }
    protocol_error("no answer was given");
}
