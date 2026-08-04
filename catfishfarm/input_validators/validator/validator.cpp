#include "validator.h"

const long long MAX_N = 100000;      // 10^5
const long long MAX_M = 300000;      // 3 * 10^5
const long long MAX_W = 1000000000;  // 10^9

void run() {
    long long maxn = Arg("maxn", MAX_N);
    // Upper bounds on the column and row of a catfish, on top of the global
    // 0 <= X[i], Y[i] <= N - 1.
    long long maxx = Arg("maxx", MAX_N - 1);
    long long maxy = Arg("maxy", MAX_N - 1);
    // Subtask 1: every X[i] is even.
    bool x_even = bool(Arg("x_even", 0));
    // Subtask 7: at most this many catfish in any single column.
    long long maxpercol = Arg("maxpercol", MAX_M);

    long long n = Int(2, maxn);
    Space();
    long long m = Int(1, MAX_M);
    Endl();

    set<pair<long long, long long>> cells;
    map<long long, long long> percol;
    for (long long i = 0; i < m; i++) {
        long long x = Int(0, min(n - 1, maxx));
        if (x_even && x % 2 != 0)
            die_line("X[" + to_string(i) + "] = " + to_string(x) + " is not even");
        Space();
        long long y = Int(0, min(n - 1, maxy));
        Space();
        Int(1, MAX_W);
        Endl();
        if (!cells.emplace(x, y).second)
            die_line("two catfish share cell (" + to_string(x) + ", " + to_string(y) + ")");
        percol[x]++;
    }

    for (auto& [col, cnt] : percol)
        if (cnt > maxpercol)
            die("column " + to_string(col) + " holds " + to_string(cnt) +
                " catfish, at most " + to_string(maxpercol) + " allowed");
}
