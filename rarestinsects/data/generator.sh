#!/usr/bin/env bash

# Local, patched copy of testdata_tools/gen.sh; see the note at its top. It makes
# accept_with_score(x) from the output validator multiply the group score by x,
# which is how the statement's score table for group 3 is applied.
. ./gen.sh

# Interactive problem: the .ans files are not expected outputs. They carry the
# per-case operation-count flag instead -- see the note below -- so the reference
# "solution" just stamps the default. It lives under data/ rather than under
# submissions/, where it would not be in a verdict directory.
SOLUTION_BASE=$PROBLEM_PATH/data
use_solution is_partial_flag.sh

# All test data is the original IOI 2022 data, imported verbatim except that the
# second field of the first line -- the is_partial flag the original grader used
# to decide whether to score the case by its operation count -- has been dropped.
# Keeping it in the input would tell a contestant which group they are in, which
# the original deliberately did not.
#
# The flag itself is not dropped: it moved to the .ans file, which is judge-side
# data and reveals nothing. See _mark_partial below.
#
# The official data contained three pairs of byte-identical cases under
# different names (1-01 = 3-01, 1-02 = 3-02, 1-03 = 3-03); only the first name
# of each pair is kept. Group membership is derived from the bound on N, so the
# sample and a few group-3 cases land in more groups than they originally did.

samplegroup
limits maxn=200
# The .ans is the official attachments/samples/sample-1.out, kept verbatim: the
# answer plus the q of the call sequence the statement walks through. This is the
# one .ans in the problem that is not a flag; 0-01 had is_partial=0, and the
# validator reads "not the word partial" as exactly that, so it is still correct
# judge-side data as well as what Kattis shows as the sample output.
sample_manual 1

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

# The cases the original package flagged is_partial=1, i.e. the ones its manager
# scored by q/N. This is the official set 3-01 ... 3-47, with the three
# deduplicated pairs resolved to the name this port keeps (3-01 = 1-01,
# 3-02 = 1-02, 3-03 = 1-03).
#
# is_partial was a property of the *test case*, not of the subtask: the original
# ran 1-01 unscored in subtasks 1, 2 and 3 and ran the identical 3-01 scored in
# subtask 3. Deduplicating those two leaves one file that must be scored in
# group 3 and not in groups 1 and 2, so the flag alone is not enough -- the
# validator applies the score table only when the group asks for it
# ("output_validator_flags partial" above) *and* the case is flagged.
PARTIAL_CASES="
1-01 1-02 1-03
3-04 3-05 3-06 3-07 3-08 3-09 3-10 3-11 3-12 3-13 3-14 3-15 3-16 3-17 3-18
3-19 3-20 3-21 3-22 3-23 3-24 3-25 3-26 3-27 3-28 3-29 3-30 3-31 3-32 3-33
3-34 3-35 3-36 3-37 3-38 3-39 3-40 3-41 3-42 3-43 3-44 3-45 3-46 3-47
"

_mark_partial () {
  # Every case is stored once and pulled into the other groups as a symlink, so
  # writing through each copy lands on the one real file.
  local name f found
  for name in $PARTIAL_CASES; do
    found=0
    for f in secret/*/[0-9][0-9][0-9]-"$name".ans; do
      [[ -e $f ]] || continue
      echo partial > "$f"
      found=1
    done
    if [[ $found = 0 ]]; then
      _error "no test case named \"$name\" to flag as partial"
    fi
  done

  # A typo above would silently switch the operation-count score off, so check
  # that every secret answer file now holds one of the two flags. The sample's is
  # the documented exception.
  local sample_ans
  sample_ans=$(readlink -f sample/1.ans)
  for f in secret/*/*.ans; do
    if [[ $(readlink -f "$f") != "$sample_ans" ]]; then
      case $(cat "$f") in
        partial | full) ;;
        *) _error "answer file $f is not a flag: \"$(cat "$f")\"" ;;
      esac
    fi
  done

  local n
  n=$(grep -lx partial secret/*/*.ans 2>/dev/null | xargs -r -n1 readlink -f | sort -u | wc -l)
  echo "Flagged $n distinct cases as operation-count scored (expected 47)."
  [[ $n = 47 ]] || _error "expected 47 partial-scored cases, flagged $n"
}

wait  # let every parallel tc finish writing its .ans before rewriting them
_mark_partial
