#!/bin/bash

flag_formating=term
flag_out_path=./out
flag_err_path=./out
flag_force=false
flag_auto_test_creation=false
flag_skip_ok=false
flag_always_continue=true
flag_skip_summary=false
flag_minimal=false
flag_very_minimal=false
flag_extreamely_minimalistic=false

input_prog_flag_acc=


C_RED=$(printf "\e[1;31m")
C_GREEN=$(printf "\e[1;32m")
C_BLUE=$(printf "\e[1;34m")
C_CYAN=$(printf "\e[1;36m")
C_PURPLE=$(printf "\e[1;35m")
C_YELLOW=$(printf "\e[1;33m")
C_GRAY=$(printf "\e[1;30m")
C_NORMAL=$(printf "\e[0m")
C_BOLD=$(printf "\e[1m")

B_DEBUG=
E_DEBUG=
B_ERR=
E_ERR=
B_INFO=
E_INFO=
B_WARN=
E_WARN=
B_BOLD=
E_BOLD=
B_OK=
E_OK=


#param_prog=$1
#shift
#param_dir=$1
#shift
#flag_good_out_path=$param_dir

param_counter=0
while test $# != 0
do
    case "$1" in
    --tsty-format) flag_formating=sty ;;
    --tterm-format) flag_formating=term ;;
    --tnone-format) flag_formating=none ;;
    --tc) flag_formating=none ;;
    --tless-info) flag_skip_ok=true ;;
    --tout) shift; flag_out_path=$1 ;;
    --terr) shift; flag_err_path=$1 ;;
    --tf) flag_force=true ;;
    --tt) flag_auto_test_creation=true ;;
    --ts) flag_skip_ok=true ;;
    --tn) flag_skip_summary=true ;;
    --ta) flag_always_continue=false ;;
    --tm) flag_skip_ok=true; flag_minimal=true ;;
    --tmm) flag_skip_ok=true; flag_minimal=true; flag_very_minimal=true ;;
    --tmmm) flag_skip_ok=true; flag_minimal=true; flag_very_minimal=true; flag_extreamely_minimalistic=true ;;
    -help) printf "\nUsage:\n     test  <prog> <dir> [flags]\n      <prog> is path to the executable, you want to test\n      <dir> is the path to folder containing .in/.out files\n      All available flags are:\n        --tsty-format - use !error!, !info! etc. output format\n        --tterm-format - use (default) term color formatting\n        --tc, --tnone-format - use clean character output\n        --ts - Skip oks\n        --terr <dir> - set .err output directory (default is /out)\n        --tout <dir> set output .out file directory (default is /out)\n        --tf - proceed even if directories do not exists etc.\n        --tt - automatically create missing .out files using program output\n        --tn - skip after-testing summary\n        --ta - abort after +5 errors\n        -help - display this help\n        --tm - use minimalistic mode (less output)\n        --tmm - use very minimalistic mode (even less output)\n        --tmmm - use the most minimialistic mode (only file names are shown)\n\n"; exit 0 ;;
    --help) printf "\nUsage:\n     test  <prog> <dir> [flags]\n      <prog> is path to the executable, you want to test\n      <dir> is the path to folder containing .in/.out files\n      All available flags are:\n        --tsty-format - use !error!, !info! etc. output format\n        --tterm-format - use (default) term color formatting\n        --tc, --tnone-format - use clean character output\n        --ts - Skip oks\n        --terr <dir> - set .err output directory (default is /out)\n        --tout <dir> set output .out file directory (default is /out)\n        --tf - proceed even if directories do not exists etc.\n        --tt - automatically create missing .out files using program output\n        --tn - skip after-testing summary\n        --ta - abort after +5 errors\n        -help - display this help\n        --tm - use minimalistic mode (less output)\n        --tmm - use very minimalistic mode (even less output)\n        --tmmm - use the most minimialistic mode (only file names are shown)\n\n"; exit 0 ;;
    *) {
      if [[ $1 == -* ]]; then
        input_prog_flag_acc="$input_prog_flag_acc $1"
      else
        if [[ "$param_counter" == 0 ]]; then
          param_counter=1
          param_prog="$1"
        else
          if [[ "$param_counter" == 1 ]]; then
            param_counter=2
            param_dir="$1"
          else
            input_prog_flag_acc="$input_prog_flag_acc $1"
          fi
        fi
      fi
    } ;;
    esac
    shift
done
flag_good_out_path="$param_dir"


if [[ ${flag_formating} = 'sty' ]]; then
  B_DEBUG="!debug!"
  E_DEBUG="!normal!"
  B_ERR="!error!"
  E_ERR="!normal!"
  B_INFO="!info!"
  E_INFO="!normal!"
  B_WARN="!warn!"
  E_WARN="!normal!"
  B_BOLD="!bold!"
  E_BOLD="!normal!"
  B_OK="!ok!"
  E_OK="!normal!"
fi

if [[ ${flag_formating} = 'term' ]]; then
  B_DEBUG=$C_GRAY
  E_DEBUG=$C_NORMAL
  B_ERR=$C_RED
  E_ERR=$C_NORMAL
  B_INFO=$C_BLUE
  E_INFO=$C_NORMAL
  B_WARN=$C_YELLOW
  E_WARN=$C_NORMAL
  B_BOLD=$C_BOLD
  E_BOLD=$C_NORMAL
  B_OK=$C_GREEN
  E_OK=$C_NORMAL
fi

if [[ ${flag_force} = 'false' ]]; then
  if [[ $param_prog = '' ]]; then
    printf "${B_DEBUG} $* ${E_DEBUG}"
    printf "${B_ERR}Tested program name was not given. (parameter <prog> is missing)${E_ERR}\n"
    printf "${B_ERR}Usage: test <prog> <input_dir> [flags]${E_ERR}\n"
    printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
    exit 1
  fi
  if [[ $param_dir = '' ]]; then
    printf "${B_ERR}Input directory was not given. (parameter <input_dir> is missing)${E_ERR}\n"
    printf "${B_ERR}Usage: test <prog> <input_dir> [flags]${E_ERR}\n"
    printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
    exit 1
  fi
  if [[ -d $param_dir ]]; then
    echo -en ""
  else
    printf "${B_ERR}Input directory \"$param_dir\" does not exists.${E_ERR}\n"
    printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
    exit 1
  fi
fi


make -pn -f build.config > ./make.db.temp 2>/dev/null
while read var assign value; do
  if [[ ${assign} = ':=' ]]; then
    eval ${var//./_}=\"$value\"
  fi
done <./make.db.temp
rm -f ./make.db.temp


mkdir -p $flag_out_path
mkdir -p $flag_err_path
rm -f -r $flag_out_path/*
rm -f -r $flag_err_path/*


#mkdir -p $TEST_RESULTS_DIR
#mkdir -p $TEST_RESULTS_DIR/out
#mkdir -p $TEST_RESULTS_DIR/err
#rm -f -r $TEST_RESULTS_DIR/out/*
#rm -f -r $TEST_RESULTS_DIR/err/*


### Initial test

command -v "$param_prog" >/dev/null 2>&1
if [ "$?" != "0" ]; then
  command -v "./$param_prog" >/dev/null 2>&1
  if [ "$?" != "0" ]; then
    command -v "./$param_prog.exe" >/dev/null 2>&1
    if [ "$?" != "0" ]; then
      command -v "./$param_prog.app" >/dev/null 2>&1
      if [ "$?" != "0" ]; then
        command -v "./$param_prog.sh" >/dev/null 2>&1
        if [ "$?" != "0" ]; then
          printf "${B_ERR}Invalid program name. Program not found.${E_ERR}\n";
          printf "${B_ERR}Please verify if the executable name is correct.${E_ERR}"
          exit 1
        else
          param_prog=./$param_prog.sh
        fi
      else
        param_prog=./$param_prog.app
      fi
    else
      param_prog=./$param_prog.exe
    fi
  else
    param_prog=./$param_prog
  fi
fi

file_count=0
for input_file_path in $param_dir/*.in
do
  file_count=$((file_count+1))
done

if [[ $flag_minimal = 'false' ]]; then
  printf "\n"
fi

#if [[ ${flag_skip_ok} = 'false' ]]; then
#  if [[ "$file_count" -gt 1 ]]; then
#    printf "${B_DEBUG}Detected large amount of input files.\nUse -s flag to skip oks :)\n${E_DEBUG}\n"
#  fi
#fi

if [[ $flag_minimal = 'false' ]]; then
  printf "${B_BOLD}Performing tests...${E_BOLD}\n"
  printf "${B_DEBUG}Call $param_prog $input_prog_flag_acc ${E_DEBUG}\n\n"
fi

file_index=1
err_index=0
ok_index=0
warn_index=0
not_exists_index=0
not_exists_but_created_index=0
for input_file_path in $param_dir/*.in
do
    if [[ -e $input_file_path ]]; then
      #TEST_RESULTS
      input_file=$(basename $input_file_path)
      good_out_path=$flag_good_out_path/${input_file/.in/.out}
      out_path=$flag_out_path/${input_file/.in/.out}
      err_path=$flag_err_path/${input_file/.in/.err}
      r=$($param_prog $input_prog_flag_acc < $input_file_path 1> $out_path 2> $err_path)
      if [ -s "$err_path" ]; then
        err_index=$((err_index+1))
        err_message=$(cat "$err_path")
        if [[ $flag_extreamely_minimalistic = 'false' ]]; then
          printf  "${B_ERR}$input_file${E_ERR}\n"
        else
          if [[ $flag_very_minimal = 'false' ]]; then
            printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_ERR}[ERR] Error at stderr${E_ERR}"
          else
            printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_ERR}[ERR] Error at stderr${E_ERR}"
            err_message=$(echo -en "$err_message" | sed "s/^/ $B_ERR\|$E_ERR  /g")
            printf  "$err_message\n"
          fi
        fi
      else

        if [[ "$err_index" -gt 5 ]]; then
          if [[ $flag_always_continue = 'false' ]]; then
            printf "\n${B_WARN}[!] Abort testing +5 errors.${E_WARN}\nDo not use --ta flag to always continue."
            exit 1
          fi
        fi

        if [ -e "$good_out_path" ]; then
          diff=$(diff --text --minimal --suppress-blank-empty --strip-trailing-cr --ignore-case --ignore-tab-expansion --ignore-trailing-space --ignore-space-change --ignore-all-space --ignore-blank-lines $out_path $good_out_path)
          if [[ $diff != '' ]]; then
            err_index=$((err_index+1))
            err_message=$diff
            err_message=$(echo -en "$err_message" | sed "s/^/ $B_ERR\|$E_ERR  /g")

            if [[ $flag_extreamely_minimalistic = 'false' ]]; then
              printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_ERR}[ERR] Non matching output${E_ERR}"
            else
              printf  "${B_ERR}$input_file${E_ERR}\n"
            fi

            if [[ $flag_very_minimal = 'false' ]]; then
              # We dont want this
              if [[ 'true' = 'false' ]]; then
                printf  "\n  ${B_ERR}_${E_ERR}  \n$err_message\n ${B_ERR}|_${E_ERR}  \n"
              else
                printf  "$err_message\n"
              fi
            fi

          else
            ok_index=$((ok_index+1))
            if [[ $flag_skip_ok = 'false' ]]; then
              printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_OK}[OK]${E_OK}"
            fi
            rm -f $err_path

          fi
        else
          warn_index=$((warn_index+1))
          if [[ ${flag_auto_test_creation} = 'true' ]]; then
            not_exists_but_created_index=$((not_exists_but_created_index+1))
            r=$($param_prog $input_prog_flag_acc < $input_file_path 1> $good_out_path 2> /dev/null)
          else
            not_exists_index=$((not_exists_index+1))
            if [[ "$not_exists_index" -lt "10" ]]; then
              if [[ ${flag_extreamely_minimalistic} = 'true' ]]; then
                printf  "${B_WARN}$input_file${E_WARN}\n"
              else
                printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_WARN}[?] $good_out_path not exists${E_WARN}"
              fi
            fi
          fi
        fi
      fi
    file_index=$((file_index+1))
    fi
done

if [[ $flag_minimal = 'false' ]]; then

  if [[ "$not_exists_index" != "0" ]]; then
    printf "  ${B_WARN} $not_exists_index output files do not exits ${E_WARN}\n"
    printf "  ${B_WARN} To create them use --tt flag. ${E_WARN}\n"
  fi

  if [[ "$not_exists_but_created_index" != "0" ]]; then
    printf "  ${B_OK} Created $not_exists_but_created_index new non-existing outputs (with --tt flag) ${E_OK}\n"
  fi

  if [[ $flag_skip_summary = 'false' ]]; then
    if [[ "$ok_index" = "$file_count" ]]; then
      printf "\n${B_OK}Done testing. All $file_count tests passes. ${E_OK}\n"
    else
      printf "\n${B_BOLD}Done testing.${E_BOLD}\n |  ${B_BOLD}TOTAL: $file_count${E_BOLD}\n |  DONE : $((file_index-1))\n |  ${B_WARN}WARN : $warn_index${E_WARN}\n |  ${B_ERR}ERR  : $err_index${E_ERR}\n |  ${B_OK}OK   : $ok_index ${E_OK}\n"
    fi
  fi

else

  if [[ $flag_extreamely_minimalistic = 'false' ]]; then
    if [[ "$ok_index" = "$file_count" ]]; then
      printf "\n${B_OK}OK${E_OK}\n"
    fi
  fi

fi
