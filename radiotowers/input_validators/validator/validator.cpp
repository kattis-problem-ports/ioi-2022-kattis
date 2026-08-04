#include "validator.h"

const long long MAX_N = 100000;      // 10^5
const long long MAX_Q = 100000;      // 10^5
const long long MAX_H = 1000000000;  // 10^9
const long long MAX_D = 1000000000;  // 10^9

void run() {
    long long maxn = Arg("maxn", MAX_N);
    long long maxq = Arg("maxq", MAX_Q);
    long long maxd = Arg("maxd", MAX_D);
    // Subtask 1: the heights first strictly increase, then strictly decrease.
    bool bitonic = bool(Arg("bitonic", 0));
    // Subtask 5: every question spans the whole row of towers.
    bool full_interval = bool(Arg("full_interval", 0));
    // Subtask 6: D is the same in every question.
    bool constant_d = bool(Arg("constant_d", 0));

    long long n = Int(1, maxn);
    Space();
    long long q = Int(1, maxq);
    Endl();

    vector<long long> h = SpacedInts<long long>(n, 1, MAX_H);
    AssertUnique(h);

    if (bitonic) {
        long long k = (long long)(max_element(h.begin(), h.end()) - h.begin());
        for (long long i = 0; i < k; i++)
            if (h[i] >= h[i + 1])
                die("heights are not bitonic: H[" + to_string(i) + "] >= H[" +
                    to_string(i + 1) + "]");
        for (long long i = k; i + 1 < n; i++)
            if (h[i] <= h[i + 1])
                die("heights are not bitonic: H[" + to_string(i) + "] <= H[" +
                    to_string(i + 1) + "]");
    }

    long long firstd = -1;
    for (long long j = 0; j < q; j++) {
        long long l = Int(0, n - 1);
        Space();
        long long r = Int(l, n - 1);
        Space();
        long long d = Int(1, maxd);
        Endl();

        if (full_interval && (l != 0 || r != n - 1))
            die("question " + to_string(j) + " is not the full interval");
        if (constant_d) {
            if (j == 0) firstd = d;
            else if (d != firstd)
                die("question " + to_string(j) + " uses D = " + to_string(d) +
                    " but question 0 used D = " + to_string(firstd));
        }
    }
}
