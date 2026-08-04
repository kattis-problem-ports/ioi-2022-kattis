#include "validator.h"

const long long MAX_N = 2000;
const long long MAX_TYPE = 1000000000;  // 10^9

void run() {
    long long maxn = Arg("maxn", MAX_N);

    long long n = Int(2, maxn);
    Endl();

    SpacedInts<long long>(n, 0, MAX_TYPE);
}
