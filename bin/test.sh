#!/bin/bash

use_formated_out=false

while test $# != 0
do
    case "$1" in
    --format) use_formated_out=true ;;
    *) echo "Unknown option was used: $1"
    esac
    shift
done


function perr { if [[ $use_formated_out = 'true' ]]; then echo -en "<error>$*</error>"; else echo -en "$*"; fi }
function pwarn { if [[ $use_formated_out = 'true' ]]; then echo -en "<warn>$*</warn>"; else echo -en "$*"; fi }
function pgood { if [[ $use_formated_out = 'true' ]]; then echo -en "<good>$*</good>"; else echo -en "$*"; fi }
function pinfo { if [[ $use_formated_out = 'true' ]]; then echo -en "$*"; else echo -en "$*"; fi }
function pdebug { if [[ $use_formated_out = 'true' ]]; then echo -en "<debug>$*</debug>"; else echo -en "$*"; fi }
function pbold { if [[ $use_formated_out = 'true' ]]; then echo -en "<b>$*</b>"; else echo -en "$*"; fi }
function pshift { echo -en "   "; }
function pendl { echo ""; }


make -pn -f build.config > ./make.db.temp 2>/dev/null
while read var assign value; do
  if [[ ${assign} = ':=' ]]; then
    eval ${var//./_}=\"$value\"
  fi
done <./make.db.temp
rm -f ./make.db.temp




mkdir -p $TEST_RESULTS_DIR
mkdir -p $TEST_RESULTS_DIR/out
mkdir -p $TEST_RESULTS_DIR/err

file_count=0
for input_file_path in $TEST_DIR/*.in
do
  file_count=$((file_count+1))
done

pbold "Performing tests..."
pendl
file_index=0
for input_file_path in $TEST_DIR/*.in
do
    if [[ -f $input_file_path ]]; then
      #TEST_RESULTS
      input_file=$(basename $input_file_path)
      out_path=$TEST_RESULTS_DIR/out/${input_file/.in/.out}
      err_path=$TEST_RESULTS_DIR/err/${input_file/.in/.err}
      $DIST_DIR/target$EXE < $input_file_path 1> $out_path 2> $err_path > /dev/null
      if [ -s "$err_path" ]; then
        pdebug [$file_index/$file_count]
        pshift
        perr $input_file
        pshift
        perr Non-empty error stream
        pendl
      else
        printf  "%-35s  %s" 
"<debug>[${file_index}/${file_count}]</debug>  
{$input_file}" "<good>[OK]</good>"
        pshift
        pinfo $input_file
        pshift
        pgood [OK]
        pendl
        rm -f $err_path
      fi
    file_index=$((file_index+1))
    fi
done
