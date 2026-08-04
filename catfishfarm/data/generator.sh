#!/usr/bin/env bash

. ../../testdata_tools/gen.sh

# Submissions are function-only files, which Kattis compiles together with
# include/cpp/grader.cpp. Build the reference the same way and use it as the
# answer generator: grader.cpp reads a .in file and prints the answers, so the
# byte stream it speaks to the judge is the same one the .in/.ans files hold.
g++ -O2 -Wall -std=gnu++20 -I ../include/cpp -o judge_model \
    ../include/cpp/grader.cpp ../submissions/accepted/prabowo_model.cpp
add_program judge_model "./judge_model"
add_cleanup judge_model
SOLUTION=judge_model

# All test data is the original IOI 2022 data, imported verbatim (only the
# leading grader-secret line of every .in file was stripped). Cases are stored
# in the lowest-numbered group that contains them and pulled into the other
# groups with include_group / tc, so no input file is duplicated on disk.
#
# The official data contained three pairs of byte-identical cases under
# different names: maxnleftcorners-01 = 3-01, 2-01 = manualn3-01 and
# 3-02 = maxnrightcorners-01. Only the first name of each pair is kept.

samplegroup
limits maxn=300 maxy=8
sample 1

group group1 3
limits x_even=1
tg_manual ../data_source/group1

group group2 6
limits maxx=1
tg_manual ../data_source/group2
tc firstcolumnoftwocolumns-01
tc firstcolumnoftwocolumns-02
tc maxnleftcorners-01
tc maxnleftcorners-02

group group3 9
limits maxy=0
tg_manual ../data_source/group3
tc maxnleftcorners-01

group group4 14
limits maxn=300 maxy=8
include_group sample
tg_manual ../data_source/group4
tc 2-01
tc manualn2-01
tc manualn2-02
tc manualn2-03
tc manualn2-04

group group5 21
limits maxn=300
include_group sample group4
tg_manual ../data_source/group5

group group6 17
limits maxn=3000
include_group sample group4 group5
tg_manual ../data_source/group6

group group7 14
limits maxpercol=2
include_group sample group3
tg_manual ../data_source/group7
tc 2-01
tc manualn2-01
tc manualn2-02
tc manualn2-03
tc manualn2-04
tc manualn3-02
tc maxnleftcorners-02
# The official subtask 7 omitted these four cases even though each has at most
# one catfish per column, so they are legal here and are pulled in.
tc 4-01
tc 4-02
tc 5-01
tc 6-01

group group8 16
include_group sample group1 group2 group3 group4 group5 group6 group7
tg_manual ../data_source/group8
