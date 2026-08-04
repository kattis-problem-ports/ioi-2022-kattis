#!/usr/bin/env bash

# Local, patched copy of testdata_tools/gen.sh; see the note at its top. It makes
# accept_with_score(x) from the output validator multiply the group score by x,
# which is how the statement's 35% partial credit is applied.
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

# All test data is the original IOI 2022 data, imported verbatim (only the
# leading grader-secret line of every .in file was stripped). Cases are stored
# in the lowest-numbered group that contains them and pulled into the other
# groups with include_group / tc, so no input file is duplicated on disk.
#
# The official data contained three pairs of byte-identical cases under
# different names (sample 2 = 1-01, 1-02 = 5-08, 1-05 = 3-03); only one name of
# each pair is kept. Group membership is derived from the subtask constraints
# rather than copied from the official subtask lists, so a few cases land in
# more groups than they originally did.

samplegroup
# Journeys are not unique, so the sample answers are the official ones, kept
# verbatim so that they match the sample explanation in the statement.
sample_manual 1
sample_manual 2

group group1 5
limits maxn=2
tg_manual ../data_source/group1
tc 2

group group2 5
limits maxn=400 complete=1
tg_manual ../data_source/group2
tc 1-05
tc completesmall-01

group group3 21
limits maxn=1000 bidirectional=1
tg_manual ../data_source/group3
tc 1-05
tc 3-11
tc completesmall-01
tc completesmall-02
tc completesmall-03
tc completesmall-04
tc completesmall-05

group group4 24
limits maxn=1000 doubled=1
tg_manual ../data_source/group4
tc 1-03
tc 1-04
tc 4-07

group group5 45
include_group sample group1 group2 group3 group4
tg_manual ../data_source/group5
