#include "validate.h"

// Interactive output validator for IOI 2022 "circuit" (Digital Circuit).
//
// The original task is a CMS Communication task: the contestant implements
// init(N, M, P, A) and count_ways(L, R), and the manager reveals the updates one
// at a time so that count_ways cannot see the ones that come after it. This
// validator is that manager. Together with include/cpp/grader.cpp it reproduces
// the original interface exactly; in particular a submission cannot read the
// whole update list up front and answer offline.
//
// Judge input file: N M Q, then P[0..N+M-1], then A[0..M-1], then Q lines "L R".
// Judge answer file: the Q expected answers.
//
// Protocol:
//   validator  -> submission : "N M Q", then P, then A
//   validator  -> submission : "L R"        (one update)
//   submission -> validator  : the answer   (repeated Q times)

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

    ll n, m, q;
    if (!(judge_in >> n >> m >> q)) judge_error("could not read N, M and Q");
    vector<ll> p(n + m), a(m);
    for (ll i = 0; i < n + m; i++)
        if (!(judge_in >> p[i])) judge_error("could not read P[%lld]", i);
    for (ll j = 0; j < m; j++)
        if (!(judge_in >> a[j])) judge_error("could not read A[%lld]", j);

    printf("%lld %lld %lld\n", n, m, q);
    for (ll i = 0; i < n + m; i++) printf("%lld%c", p[i], i + 1 == n + m ? '\n' : ' ');
    for (ll j = 0; j < m; j++) printf("%lld%c", a[j], j + 1 == m ? '\n' : ' ');
    fflush(stdout);

    for (ll k = 0; k < q; k++) {
        ll l, r;
        if (!(judge_in >> l >> r)) judge_error("could not read update %lld", k);
        ll expected;
        if (!(judge_ans >> expected)) judge_error("no judge answer for update %lld", k);

        printf("%lld %lld\n", l, r);
        fflush(stdout);

        ll got;
        if (!(author_out >> got))
            wrong_answer("No answer to update %lld (of %lld)\n", k, q);
        if (got != expected)
            wrong_answer("Update %lld: answered %lld, expected %lld\n", k, got, expected);
    }

    string trailing;
    if (author_out >> trailing) wrong_answer("Output after the last answer\n");

    ll leftover;
    if (judge_ans >> leftover) judge_error("judge answer file has more than %lld answers", q);

    accept();
}
