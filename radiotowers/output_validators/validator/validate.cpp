#include "validate.h"

// Interactive output validator for IOI 2022 "towers" (Radio Towers).
//
// The original task is a CMS Communication task: the contestant implements
// init(N, H) and max_towers(L, R, D), and the manager reveals the questions one
// at a time so that max_towers cannot see the ones that come after it. This
// validator is that manager. Together with include/cpp/grader.cpp it reproduces
// the original interface exactly; in particular a submission cannot read the
// whole question list up front and answer offline.
//
// Judge input file: N Q, then H[0..N-1], then Q lines "L R D".
// Judge answer file: the Q expected answers.
//
// Protocol:
//   validator  -> submission : "N Q", then the N heights
//   validator  -> submission : "L R D"          (one question)
//   submission -> validator  : the answer       (repeated Q times)

#include <csignal>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

using ll = long long;

int main(int argc, char** argv) {
    init_io(argc, argv);
    // If the submission dies early, keep running so a verdict can be reported.
    signal(SIGPIPE, SIG_IGN);

    ll n, q;
    if (!(judge_in >> n >> q)) judge_error("could not read N and Q");
    vector<ll> h(n);
    for (ll i = 0; i < n; i++)
        if (!(judge_in >> h[i])) judge_error("could not read H[%lld]", i);

    printf("%lld %lld\n", n, q);
    for (ll i = 0; i < n; i++) printf("%lld%c", h[i], i + 1 == n ? '\n' : ' ');
    fflush(stdout);

    for (ll j = 0; j < q; j++) {
        ll l, r, d;
        if (!(judge_in >> l >> r >> d)) judge_error("could not read question %lld", j);
        ll expected;
        if (!(judge_ans >> expected)) judge_error("no judge answer for question %lld", j);

        printf("%lld %lld %lld\n", l, r, d);
        fflush(stdout);

        ll got;
        if (!(author_out >> got))
            wrong_answer("No answer to question %lld (of %lld)\n", j, q);
        if (got != expected)
            wrong_answer("Question %lld: answered %lld, expected %lld\n", j, got, expected);
    }

    string trailing;
    if (author_out >> trailing) wrong_answer("Output after the last answer\n");

    ll leftover;
    if (judge_ans >> leftover) judge_error("judge answer file has more than %lld answers", q);

    accept();
}
