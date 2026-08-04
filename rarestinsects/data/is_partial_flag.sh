#!/usr/bin/env bash
# The problem is interactive: the output validator scores the live run, so a .ans
# file is not an expected output here. It carries instead the one piece of
# judge-side data the scoring needs -- whether this test case is scored by its
# operation count. See the note in generator.sh.
#
# Every case starts out "full"; generator.sh then rewrites the 47 that the
# original package flagged is_partial=1.
cat > /dev/null
echo full
