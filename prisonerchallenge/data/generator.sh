#!/usr/bin/env bash

# Local, patched copy of testdata_tools/gen.sh; see the note at its top. It makes
# accept_with_score(x) from the output validator multiply the group score by x,
# which is how the statement's score table for group 3 is applied.
. ./gen.sh

# Submissions are function-only files, which Kattis compiles together with
# include/cpp/grader.cpp. Build the reference the same way and use it as the
# answer generator: grader.cpp reads a .in file and prints the answers, so the
# byte stream it speaks to the judge is the same one the .in/.ans files hold.
g++ -O2 -Wall -std=gnu++20 -I ../include/cpp -o judge_model \
    ../include/cpp/grader.cpp ../submissions/accepted/model.cpp
add_program judge_model "./judge_model"
add_cleanup judge_model
SOLUTION=judge_model

# The input of a test case is just N, so the test data is one case per distinct
# N that the original data used: the union of the N values of the official
# subtasks 1, 2 and 3, deduplicated. The per-group cap on x is not part of the
# input (the original passed it to the grader out of band, so that contestants
# could not tell the subtasks apart); here it is an output validator flag.
#
# Groups 1 and 2 therefore have identical inputs and differ only in the cap on
# x, so group2 is exactly include_group group1.

samplegroup
limits maxn=500
# Many strategies are valid, so the sample answer is the one spelled out in the
# statement rather than whatever the model solution happens to produce.
sample_manual 1

group group1 5
limits maxn=500
output_validator_flags maxx=500
tg_manual ../data_source/group1
tc 1

group group2 5
limits maxn=500
output_validator_flags maxx=70
include_group group1

group group3 90
output_validator_flags maxx=60 partial
include_group group1 group2
tg_manual ../data_source/group3
