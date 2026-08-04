#include "validator.h"

const long long MAX_N = 100000;  // 10^5
const long long MAX_M = 200000;  // 2 * 10^5

void run() {
    long long maxn = Arg("maxn", MAX_N);
    // Subtask 2: for every pair of distinct islands x < y there are exactly two
    // canoes between them, one initially docked at x and one at y.
    bool complete = bool(Arg("complete", 0));
    // Subtask 3: canoes come in pairs i, i+1 (i even) between the same two
    // islands, docked at opposite ends.
    bool bidirectional = bool(Arg("bidirectional", 0));
    // Subtask 4: canoes come in pairs i, i+1 (i even) between the same two
    // islands, both docked at the same end.
    bool doubled = bool(Arg("doubled", 0));

    long long n = Int(2, maxn);
    Space();
    long long m = Int(1, MAX_M);
    Endl();

    if ((bidirectional || doubled) && m % 2 != 0)
        die("M = " + to_string(m) + " must be even");
    if (complete && m != n * (n - 1))
        die("M = " + to_string(m) + " must equal N * (N - 1) = " +
            to_string(n * (n - 1)));

    vector<long long> u(m), v(m);
    for (long long i = 0; i < m; i++) {
        u[i] = Int(0, n - 1);
        Space();
        v[i] = Int(0, n - 1);
        Endl();
        if (u[i] == v[i])
            die_line("canoe " + to_string(i) + " has U[i] = V[i] = " + to_string(u[i]));
    }

    if (complete) {
        set<pair<long long, long long>> seen;
        for (long long i = 0; i < m; i++)
            if (!seen.emplace(u[i], v[i]).second)
                die("two canoes are docked at island " + to_string(u[i]) +
                    " and sail to island " + to_string(v[i]));
        // Exactly n*(n-1) distinct ordered pairs of distinct islands exist, and
        // m equals that count, so seeing each at most once means seeing each
        // exactly once.
    }

    if (bidirectional) {
        for (long long i = 0; i < m; i += 2)
            if (u[i] != v[i + 1] || v[i] != u[i + 1])
                die("canoes " + to_string(i) + " and " + to_string(i + 1) +
                    " are not a bidirectional pair");
    }

    if (doubled) {
        for (long long i = 0; i < m; i += 2)
            if (u[i] != u[i + 1] || v[i] != v[i + 1])
                die("canoes " + to_string(i) + " and " + to_string(i + 1) +
                    " are not a doubled pair");
    }
}
