#!/usr/bin/env bash

. ../../testdata_tools/gen.sh

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

samplegroup
sample 1

group group1 4
limits bitonic=1
tg_manual ../data_source/group1
# The official subtask 1 omitted several cases whose heights are monotone
# (hence bitonic); they are legal here and are pulled in.

group group2 11
limits maxq=1 maxn=2000
tg_manual ../data_source/group2
tc 2-08
tc 2-09
tc bitonicquadraticdequalsone-01
tc bitonicquadraticdequalsone-02
tc bitonicquadraticdequalsone-03
tc quadraticdequalsone-04
tc quadraticdequalsonefullinterval-04
tc quadraticfullinterval-08
tc quadraticfullinterval-09

group group3 12
limits maxq=1
include_group group2
tg_manual ../data_source/group3
tc 3-08
tc 3-09
tc lineardequalsone-04
tc lineardequalsonefullinterval-04
tc linearfullinterval-08
tc linearfullinterval-09

group group4 14
limits maxd=1
tg_manual ../data_source/group4
tc 4-08
tc 4-09
tc bitonicdequalsone-01
tc bitonicdequalsone-02
tc bitonicquadraticdequalsone-01
tc bitonicquadraticdequalsone-02
tc bitonicquadraticdequalsone-03
tc lineardequalsone-01
tc lineardequalsone-02
tc lineardequalsone-03
tc lineardequalsone-04
tc lineardequalsone-05
tc lineardequalsonefullinterval-01
tc lineardequalsonefullinterval-02
tc lineardequalsonefullinterval-03
tc lineardequalsonefullinterval-04
tc lineardequalsonefullinterval-05
tc quadraticdequalsone-01
tc quadraticdequalsone-02
tc quadraticdequalsone-03
tc quadraticdequalsone-04
tc quadraticdequalsone-05
tc quadraticdequalsonefullinterval-01
tc quadraticdequalsonefullinterval-02
tc quadraticdequalsonefullinterval-03
tc quadraticdequalsonefullinterval-04
tc quadraticdequalsonefullinterval-05

group group5 17
limits full_interval=1
tg_manual ../data_source/group5
tc 5-08
tc 5-09
tc lineardequalsonefullinterval-01
tc lineardequalsonefullinterval-02
tc lineardequalsonefullinterval-03
tc lineardequalsonefullinterval-04
tc lineardequalsonefullinterval-05
tc linearfullinterval-01
tc linearfullinterval-02
tc linearfullinterval-03
tc linearfullinterval-04
tc linearfullinterval-05
tc linearfullinterval-06
tc linearfullinterval-07
tc linearfullinterval-08
tc linearfullinterval-09
tc linearfullinterval-10
tc linearfullinterval-11
tc quadraticdequalsonefullinterval-01
tc quadraticdequalsonefullinterval-02
tc quadraticdequalsonefullinterval-03
tc quadraticdequalsonefullinterval-04
tc quadraticdequalsonefullinterval-05
tc quadraticfullinterval-01
tc quadraticfullinterval-02
tc quadraticfullinterval-03
tc quadraticfullinterval-04
tc quadraticfullinterval-05
tc quadraticfullinterval-06
tc quadraticfullinterval-07
tc quadraticfullinterval-08
tc quadraticfullinterval-09
tc quadraticfullinterval-10
tc quadraticfullinterval-11

group group6 19
limits constant_d=1
include_group group2 group3 group4
tg_manual ../data_source/group6
tc 6-08
tc 6-09

group group7 23
include_group sample group1 group2 group3 group4 group5 group6
tg_manual ../data_source/group7
