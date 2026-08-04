#include "validator.h"

const long long MAX_N = 5000;

void run() {
    long long maxn = Arg("maxn", MAX_N);
    Int(2, maxn);
    Endl();
}
