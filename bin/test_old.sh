#!/bin/bash

flag_use_formated_out=false
flag_less_info=false


while test $# != 0
do
    case "$1" in
    --format) flag_use_formated_out=true ;;
    --less-info) flag_less_info=true ;;
    *) echo "Unknown option was used: $1"
    esac
    shift
done


function perr { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "<error>$*</error>"; else echo -en "$*"; fi }
function pwarn { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "<warn>$*</warn>"; else echo -en "$*"; fi }
function pgood { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "<good>$*</good>"; else echo -en "$*"; fi }
function pinfo { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "$*"; else echo -en "$*"; fi }
function pdebug { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "<debug>$*</debug>"; else echo -en "$*"; fi }
function pbold { if [[ $flag_use_formated_out = 'true' ]]; then echo -en "<b>$*</b>"; else echo -en "$*"; fi }
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

rm -f -r $TEST_RESULTS_DIR/out/*
rm -f -r $TEST_RESULTS_DIR/err/*


file_count=0
for input_file_path in $TEST_DIR/in/*.in
do
  file_count=$((file_count+1))
done

if [[ $flag_use_formated_out = 'true' ]]; then
  printf "<b>Performing tests...</b>\n"
else
  printf "Performing tests...\n"
fi
file_index=1
err_index=0
for input_file_path in $TEST_DIR/in/*.in
do
    if [[ -f $input_file_path ]]; then
      #TEST_RESULTS
      input_file=$(basename $input_file_path)
      good_out_path=$TEST_DIR/out/${input_file/.in/.out}
      out_path=$TEST_RESULTS_DIR/out/${input_file/.in/.out}
      err_path=$TEST_RESULTS_DIR/err/${input_file/.in/.err}
      $DIST_DIR/target$EXE < $input_file_path 1> $out_path 2> $err_path
      if [ -s "$err_path" ]; then
        err_message=$(cat "$err_path")
        if [[ $flag_use_formated_out = 'true' ]]; then
          printf  "%-35s  %s\n" "<debug>[$file_index/$file_count]</debug>  $input_file" "<error>[ERR] Error at stderr</error>"
          printf  "!error!$err_message!normal!\n"
        else
          printf  "%-35s  %s\n" "[$file_index/$file_count]  $input_file" "[ERR] Error at stderr"
          printf  "$err_message\n"
        fi
      else
        err_index=$((err_index+1))
        if [[ $err_index == 5 ]]; then
          if [[ $flag_use_formated_out = 'true' ]]; then
            printf "\n<warn>[!] Abort testing +5 errors.<warn>\n"
          else
            printf "\n[!] Abort testing +5 errors.\n"
          fi
          exit 1
        fi

        if [ -s "$good_out_path" ]; then
          diff=$(diff --text --minimal --suppress-blank-empty --strip-trailing-cr --ignore-case --ignore-tab-expansion --ignore-trailing-space --ignore-space-change --ignore-all-space --ignore-blank-lines $out_path $good_out_path)
          if [[ $diff != '' ]]; then

            err_message=$diff
            if [[ $flag_use_formated_out = 'true' ]]; then
              printf  "%-35s  %s\n" "<debug>[$file_index/$file_count]</debug>  $input_file" "<error>[ERR] Non matching output</error>"
              printf  "!error!$err_message!normal!\n"
            else
              printf  "%-35s  %s\n" "[$file_index/$file_count]  $input_file" "[ERR] Non matching output"
              printf  "$err_message\n"
            fi

          else

            if [[ $flag_less_info = 'false' ]]; then
              if [[ $flag_use_formated_out = 'true' ]]; then
                printf  "%-35s  %s\n" "<debug>[$file_index/$file_count]</debug>  $input_file" "<good>[OK]</good>"
              else
                printf  "%-35s  %s\n" "[$file_index/$file_count]  $input_file" "[OK]"
              fi
            fi
            rm -f $err_path

          fi
        else

          if [[ $flag_use_formated_out = 'true' ]]; then
            printf  "%-35s  %s\n" "<debug>[$file_index/$file_count]</debug>  $input_file" "<warn>[?] $good_out_path not exists</warn>"
          else
            printf  "%-35s  %s\n" "[$file_index/$file_count]  $input_file" "[?] $good_out_path not exists "
          fi

        fi
      fi
    file_index=$((file_index+1))
    fi
done
