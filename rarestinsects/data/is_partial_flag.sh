#!/usr/bin/env bash
# The problem is interactive: the output validator scores the live run and never
# reads the .ans files. gen.sh still wants a reference solution to run over every
# .in file, so this one consumes the input and writes nothing.
cat > /dev/null
