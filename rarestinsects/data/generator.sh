#!/usr/bin/env bash

# Local, patched copy of testdata_tools/gen.sh; see the note at its top. It makes
# accept_with_score(x) from the output validator multiply the group score by x,
# which is how the statement's score table for group 3 is applied.
. ./gen.sh

# Interactive problem: the .ans files are unused, so they are produced by a
# reference "solution" that prints nothing. It lives under data/ rather than
# under submissions/, where it would not be in a verdict directory.
SOLUTION_BASE=$PROBLEM_PATH/data
use_solution empty_answer.sh

# All test data is the original IOI 2022 data, imported verbatim except that the
# second field of the first line -- a flag the original grader used to decide
# whether the subtask had the operation-count score -- has been dropped. That
# flag is an output validator flag here, so that nothing in the input reveals
# which group a case belongs to.
#
# The official data contained three pairs of byte-identical cases under
# different names (1-01 = 3-01, 1-02 = 3-02, 1-03 = 3-03); only the first name
# of each pair is kept. Group membership is derived from the bound on N, so the
# sample and a few group-3 cases land in more groups than they originally did.

samplegroup
limits maxn=200
sample 1

group group1 10
limits maxn=200
include_group sample
tg_manual ../data_source/group1

group group2 15
limits maxn=1000
include_group sample group1
tg_manual ../data_source/group2

group group3 75
output_validator_flags partial
include_group sample group1 group2
tg_manual ../data_source/group3
