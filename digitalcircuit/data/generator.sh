#!/usr/bin/env bash

. ../../testdata_tools/gen.sh

# The model solution recurses once per gate, so it needs more than the default
# stack on the deep-path cases. Kattis gives submissions a stack as large as the
# memory limit, so this only matters while generating.
ulimit -s 262144  # 256 MiB; "unlimited" breaks AddressSanitizer

# Submissions are function-only files, which Kattis compiles together with
# include/cpp/grader.cpp. Build the reference the same way and use it as the
# answer generator: grader.cpp reads a .in file and prints the answers, so the
# byte stream it speaks to the judge is the same one the .in/.ans files hold.
g++ -O2 -Wall -std=gnu++20 -I ../include/cpp -o judge_model \
    ../include/cpp/grader.cpp ../submissions/accepted/model.cpp
add_program judge_model "./judge_model"
add_cleanup judge_model
SOLUTION=judge_model

# All test data is the original IOI 2022 data, imported verbatim (only the
# leading grader-secret line of every .in file was stripped). Cases are stored
# in the lowest-numbered group that contains them and pulled into the other
# groups with include_group / tc, so no input file is duplicated on disk.
#
# The official data contained one pair of byte-identical cases under different
# names (1-01 = 2-01); only the first name is kept. Group membership is derived
# from the subtask constraints rather than copied from the official subtask
# lists, so a few cases -- including the sample, which the official data left
# out of every subtask -- land in more groups than they originally did.

samplegroup
limits maxn=1000 maxm=1000 maxq=5
sample 1

group group1 2
limits maxn=1 maxm=1000 maxq=5
tg_manual ../data_source/group1

group group2 7
limits maxn=1000 maxm=1000 maxq=5 two_inputs=1
tg_manual ../data_source/group2
tc 1-01

group group3 9
limits maxn=1000 maxm=1000 maxq=5
include_group sample group1 group2
tg_manual ../data_source/group3

group group4 4
limits perfect=1 point_update=1
tg_manual ../data_source/group4

group group5 12
limits perfect=1
include_group group4
tg_manual ../data_source/group5
tc 1-01
tc 2-02
tc 2-03
tc 2-04
tc 2-05

group group6 27
limits two_inputs=1
include_group group2 group4 group5
tg_manual ../data_source/group6

group group7 28
limits maxn=5000 maxm=5000
include_group sample group1 group2 group3
tg_manual ../data_source/group7
tc 7-12
tc quadraticperfect-01
tc quadraticperfect-02
tc quadraticperfect-03
tc quadraticperfect-04

group group8 11
include_group sample group1 group2 group3 group4 group5 group6 group7
tg_manual ../data_source/group8
