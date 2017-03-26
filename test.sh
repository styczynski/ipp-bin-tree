#!/bin/bash
#
# Script for testing solution program.
# Usage:
#   test.sh <program_path> <test_folder> [-v]
#
#

flag_v=false

prog=$1
shift
dir=$1
shift

while test $# != 0
do
    case "$1" in
    -v) {
      flag_v=true
    };;
    *) {
      echo "Unknown comand option used: $1"
      exit 1
    };;
    esac
    shift
done

if [[ "$flag_v" == "false" ]]; then
  bash ./bin/shell/test.sh  --tgout "$dir" --terr "./tests_results/err" --tout "./tests_results/out" --tterm-format "$prog" "$dir"
else
  bash ./bin/shell/test.sh --tgout "$dir" --tgerr "$dir" --terr "./tests_results/err" --tout "./tests_results/out" --tterm-format  "$prog" "$dir" -v
fi
