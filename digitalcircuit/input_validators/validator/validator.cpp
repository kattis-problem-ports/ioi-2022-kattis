#include "validator.h"

const long long MAX_N = 100000;  // 10^5
const long long MAX_M = 100000;  // 10^5
const long long MAX_Q = 100000;  // 10^5

void run() {
    long long maxn = Arg("maxn", MAX_N);
    long long maxm = Arg("maxm", MAX_M);
    long long maxq = Arg("maxq", MAX_Q);
    // Subtasks 2 and 6: every threshold gate has exactly two inputs.
    bool two_inputs = bool(Arg("two_inputs", 0));
    // Subtasks 4 and 5: M = N + 1 is a power of two and P[i] = floor((i-1)/2),
    // i.e. the circuit is a perfect binary tree.
    bool perfect = bool(Arg("perfect", 0));
    // Subtask 4: every update toggles a single source gate.
    bool point_update = bool(Arg("point_update", 0));

    long long n = Int(1, maxn);
    Space();
    long long m = Int(1, maxm);
    Space();
    long long q = Int(1, maxq);
    Endl();

    if (perfect) {
        if (m != n + 1)
            die("M must equal N + 1, got N = " + to_string(n) + ", M = " + to_string(m));
        if ((m & (m - 1)) != 0)
            die("M = " + to_string(m) + " is not a power of two");
    }

    vector<long long> indeg(n, 0);
    for (long long i = 0; i < n + m; i++) {
        if (i) Space();
        if (i == 0) {
            Int(-1, -1);
            continue;
        }
        long long p = Int(0, min(i - 1, n - 1));
        if (perfect && p != (i - 1) / 2)
            die("P[" + to_string(i) + "] = " + to_string(p) + ", expected " +
                to_string((i - 1) / 2));
        indeg[p]++;
    }
    Endl();

    for (long long i = 0; i < n; i++) {
        if (indeg[i] == 0) die("threshold gate " + to_string(i) + " has no inputs");
        if (two_inputs && indeg[i] != 2)
            die("threshold gate " + to_string(i) + " has " + to_string(indeg[i]) +
                " inputs, expected 2");
    }

    SpacedInts<long long>(m, 0, 1);  // A

    for (long long k = 0; k < q; k++) {
        long long l = Int(n, n + m - 1);
        Space();
        long long r = Int(l, n + m - 1);
        Endl();
        if (point_update && l != r)
            die("update " + to_string(k) + " is not a single gate");
    }
}
