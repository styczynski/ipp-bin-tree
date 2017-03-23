#!/bin/bash

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
  echo "Use no -v flag"
  bash ./bin/shell/test.sh "$prog" "$dir" --tgout "$dir" --terr "./tests_results/err" --tout "./tests_results/out" --tterm-format
else
  bash ./bin/shell/test.sh "$prog" "$dir" --tgout "$dir" --tgerr "$dir" --terr "./tests_results/err" --tout "./tests_results/out" --tterm-format -v
fi
