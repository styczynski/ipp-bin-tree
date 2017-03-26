#!/bin/bash
#
# Script for testing solution program.
# Usage:
#   test.sh <program_path> <test_folder> [-v]
#
#

flag_v=false


dir_cnt=0
while test $# != 0
do
    case "$1" in
    -v) {
      flag_v=true
    };;
    -*) {
      echo "Invalid switch was used: $1"
      exit 1
    };;
    *) {
      if [[ $dir_cnt = 0 ]]; then
        prog=$1
      elif [[ $dir_cnt = 1 ]]; then
	dir=$1
      else
        echo "Invalid data among script parameters: $1"
	exit 1
      fi
      dir_cnt=$((dir_cnt+1))
    };;
    esac
    shift
done

if [[ "$flag_v" == "false" ]]; then
  bash ./bin/shell/test.sh --tc --tmmm --tgout "$dir" --terr "./tests_results/err" --tout "./tests_results/out"  "$prog" "$dir"
else
  bash ./bin/shell/test.sh --tc --tmmm --tgout "$dir" --tgerr "$dir" --terr "./tests_results/err" --tout "./tests_results/out" "$prog" "$dir" -v
fi
