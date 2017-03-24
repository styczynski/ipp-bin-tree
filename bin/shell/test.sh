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
flag_always_need_good_err=false
flag_good_err_path=
input_prog_flag_acc=
flag_default_require_err_emptyness=false
flag_always_ignore_stderr=false

flag_out_path=./test_out_temp
flag_err_path=./test_out_temp
flag_err_temp=true
flag_out_temp=true

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

function clean_temp {
  if [[ ${flag_out_temp} = 'true' ]]; then
    rm -f -r $flag_out_path
  fi
  if [[ ${flag_err_temp} = 'true' ]]; then
    rm -f -r $flag_err_path
  fi
}

function print_help {
  printf "\n"
  printf "Usage:\n"
  printf "    test  [test_flags] <prog> <dir> [prog_flags]\n"
  printf "      <prog> is path to the executable, you want to test\n"
  printf "      <dir> is the path to folder containing .in/.out files\n"
  printf "      [prog_flags] are optional conmmand line argument passed to program <prog>\n"
  printf "      [test_flags] are optional flags for test script\n"
  printf "      All available [test_flags] are:\n"
  printf "        --tflags - enable --t* flags interpreting at any place among command line arguments (by default flags after dir are expected to be program flags)\n"
  printf "        --tsty-format - use !error!, !info! etc. output format\n"
  printf "        --tterm-format - use (default) term color formatting\n"
  printf "        --tc, --tnone-format - use clean character output\n"
  printf "        --ts - Skip oks\n"
  printf "        --tierr - Always ignore stderr output.\n"
  printf "        --tgout <dir> - set (good) .out input directory (default is the same as dir/inputs will be still found in dir location/use when .out and .in are in separate locations)\n"
  printf "        --tgerr <dir> same as --tgout but says where to find good .err files (by default nonempty .err file means error)\n"
  printf "        --terr <dir> - set .err output directory (default is /out)\n"
  printf "        --tout <dir> set output .out file directory (default is /out)\n"
  printf "        --tf - proceed even if directories do not exists etc.\n"
  printf "        --tneed-err, --tnerr - Always need .err files (by default missing good .err files are ignored)\n"
  printf "           If --tnerr flag is used and --tgerr not specified the good .err files are beeing searched in <dir> folder.\n"
  printf "        --te, --tdefault-no-err - If the .err file not exists (ignored by default) require stderr to be empty\n"
  printf "        --tt - automatically create missing .out files using program output\n"
  printf "        --tn - skip after-testing summary\n"
  printf "        --ta - abort after +5 errors\n"
  printf "        -help - display this help\n"
  printf "        --tm - use minimalistic mode (less output)\n"
  printf "        --tmm - use very minimalistic mode (even less output)\n"
  printf "        --tmmm - use the most minimialistic mode (only file names are shown)\n"
  printf "      Wherever -help,--help flags are placed the script always displays its help info.\n"
  printf "\n"
  printf "      About minimalistic modes:\n"
  printf "         In --tm mode OKs are not printed / erors are atill full with diff\n"
  printf "         In --tmm mode errors are only generally descripted / OK at output on success\n"
  printf "         In --tmmm only names of error files are printed / Nothing at output on success\n"
  printf "\n"
}

#param_prog=$1
#shift
#param_dir=$1
#shift
#flag_good_out_path=$param_dir

param_counter=0
tflags_loading_enabled=true
tflags_always_load_all=false
while test $# != 0
do
    if [[ ${tflags_loading_enabled} = 'true' ]]; then
      case "$1" in
      --tierr) flag_always_ignore_stderr=true ;;
      --tdefault-no-err) flag_default_require_err_emptyness=true ;;
      --te) flag_default_require_err_emptyness=true ;;
      --tflags) tflags_always_load_all=true ;;
      --tneed-err) flag_always_need_good_err=true ;;
      --tnerr) flag_always_need_good_err=true ;;
      --tgout) shift; flag_good_out_path="$1" ;;
      --tgerr) shift; flag_good_err_path="$1" ;;
      --tsty-format) flag_formating=sty ;;
      --tterm-format) flag_formating=term ;;
      --tnone-format) flag_formating=none ;;
      --tc) flag_formating=none ;;
      --tless-info) flag_skip_ok=true ;;
      --tout) shift; flag_out_path="$1"; flag_out_temp=false ;;
      --terr) shift; flag_err_path="$1"; flag_err_temp=false ;;
      --tf) flag_force=true ;;
      --tt) flag_auto_test_creation=true ;;
      --ts) flag_skip_ok=true ;;
      --tn) flag_skip_summary=true ;;
      --ta) flag_always_continue=false ;;
      --tm) flag_skip_ok=true; flag_minimal=true ;;
      --tmm) flag_skip_ok=true; flag_minimal=true; flag_very_minimal=true ;;
      --tmmm) flag_skip_ok=true; flag_minimal=true; flag_very_minimal=true; flag_extreamely_minimalistic=true ;;
      -help) print_help; exit 0;;
      --help) print_help; exit 0;;
      #--t*) printf "ERROR: Unknown test flag: $1 (all flags prefixed with --t* are recognized as test flags)\n"; exit 1 ;;
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
              if [[ "$flag_good_out_path" = "" ]]; then
                flag_good_out_path="$1"
              fi
              if [[ ${tflags_always_load_all} = 'false' ]]; then
                tflags_loading_enabled=false
              fi
            else
              input_prog_flag_acc="$input_prog_flag_acc $1"
            fi
          fi
        fi
      } ;;
      esac
    else
      case "$1" in
        -help) print_help; exit 0;;
        --help) print_help; exit 0;;
        *) input_prog_flag_acc="$input_prog_flag_acc $1" ;;
      esac
    fi
    shift
done

if [[ ${flag_always_need_good_err} = 'true' ]]; then
  if [[ ${flag_good_err_path} = '' ]]; then
    flag_good_err_path=$param_dir
  fi
fi


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
    clean_temp
    exit 1
  fi
  if [[ $param_dir = '' ]]; then
    # USE AUTOFIND

    #find . -type f -name "*.txt" -printf '%h\n' | sort | uniq
    best_test_dir=$(find . -type f -name "*.in" -printf '%h\n' | sort | uniq -c | sort -k 1 -r | awk  '{print $2}' | head -n 1)

    if [[ ${best_test_dir} = '' ]]; then
      printf "${B_ERR}Input directory was not given. (parameter <input_dir> is missing)${E_ERR}\n"
      printf "${B_ERR}Usage: test <prog> <input_dir> [flags]${E_ERR}\n"
      printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
      clean_temp
      exit 1
    else
      #printf "${B_WARN}Input directory was not given. (parameter <input_dir> is missing)${E_WARN}\n"
      printf "${B_DEBUG}Autodected \'$best_test_dir\' as best test directory. Using it.${E_DEBUG}\n"
      param_dir="$best_test_dir"
      if [[ "$flag_good_out_path" = "" ]]; then
        flag_good_out_path="$param_dir"
      fi
    fi

    #printf "${B_ERR}Input directory was not given. (parameter <input_dir> is missing)${E_ERR}\n"
    #printf "${B_ERR}Usage: test <prog> <input_dir> [flags]${E_ERR}\n"
    #printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
    #clean_temp
    #exit 1
  fi
  if [[ -d $param_dir ]]; then
    echo -en ""
  else
    printf "${B_ERR}Input directory \"$param_dir\" does not exists.${E_ERR}\n"
    printf "${B_DEBUG}Use -f option to forcefully proceed.${E_DEBUG}\n"
    clean_temp
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
          clean_temp
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
for input_file_path in `ls -v $param_dir/*.in`
do
    if [[ -e $input_file_path ]]; then
      #TEST_RESULTS
      input_file=$(basename $input_file_path)
      good_out_path=$flag_good_out_path/${input_file/.in/.out}
      good_err_path=$flag_good_err_path/${input_file/.in/.err}

      out_path=$flag_out_path/${input_file/.in/.out}
      err_path=$flag_err_path/${input_file/.in/.err}


      r=$($param_prog $input_prog_flag_acc < $input_file_path 1> $out_path 2> $err_path)

      was_error=false
      print_error_by_default=true
      if [[ "$flag_always_ignore_stderr" = "false" ]]; then
        if [[ "$flag_good_err_path" != "" ]]; then

          if [ -s "$good_err_path" ]; then
            diff=$(diff --text --minimal --suppress-blank-empty --strip-trailing-cr --ignore-case --ignore-tab-expansion --ignore-trailing-space --ignore-space-change --ignore-all-space --ignore-blank-lines $err_path $good_err_path)
            if [[ $diff != '' ]]; then
              was_error=true
              print_error_by_default=false

              err_index=$((err_index+1))
              err_message=$diff
              err_message=$(echo -en "$err_message" | sed "s/^/ $B_ERR\|$E_ERR  /g")

              if [[ $flag_extreamely_minimalistic = 'false' ]]; then
                printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $err_path" "${B_ERR}[ERR] Non matching err-output${E_ERR}"
              else
                printf  "${B_ERR}$err_path${E_ERR}\n"
              fi

              if [[ $flag_very_minimal = 'false' ]]; then
                # We dont want this
                if [[ 'true' = 'false' ]]; then
                  printf  "\n  ${B_ERR}_${E_ERR}  \n$err_message\n ${B_ERR}|_${E_ERR}  \n"
                else
                  printf  "$err_message\n"
                fi
              fi
            fi

          else


            if [[ ${flag_always_need_good_err} = 'true' ]]; then

              warn_index=$((warn_index+1))
              if [[ ${flag_auto_test_creation} = 'true' ]]; then
                not_exists_but_created_index=$((not_exists_but_created_index+1))
                r=$($param_prog $input_prog_flag_acc < $input_file_path 2> $good_err_path 1> /dev/null)
              else
                not_exists_index=$((not_exists_index+1))
                if [[ "$not_exists_index" -lt "10" ]]; then
                  if [[ ${flag_extreamely_minimalistic} = 'true' ]]; then
                    printf  "${B_WARN}$good_err_path${E_WARN}\n"
                  else
                    printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_WARN}[?] $good_err_path not exists${E_WARN}"
                  fi
                fi
              fi

            else
              if [[ "$flag_default_require_err_emptyness" = "true" ]]; then
                if [ -s "$err_path" ]; then
                  was_error=true
                fi
              else
                # ERR NOT EXISTS
                # DO NOTHING BY DEFAULT
                echo -en ""
              fi
            fi

          fi

        else
          if [ -s "$err_path" ]; then
            was_error=true
          fi
        fi

      fi
      if [[ "$was_error" = "true" ]]; then
        if [[ "$print_error_by_default" = "true" ]]; then
          err_index=$((err_index+1))
          err_message=$(cat "$err_path")
          if [[ $flag_extreamely_minimalistic = 'true' ]]; then
            printf  "${B_ERR}$input_file${E_ERR}\n"
          else
            if [[ $flag_very_minimal = 'true' ]]; then
              printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_ERR}[ERR] Error at stderr${E_ERR}"
            else
              printf  "%-35s  %s\n" "${B_DEBUG}[$file_index/$file_count]${E_DEBUG}  $input_file" "${B_ERR}[ERR] Error at stderr${E_ERR}"
              err_message=$(echo -en "$err_message" | sed "s/^/ $B_ERR\|$E_ERR  /g")
              printf  "$err_message\n"
            fi
          fi
        fi

        if [[ ${flag_out_temp} = 'true' ]]; then
          rm -f -r $flag_out_path/*
        fi
        if [[ ${flag_err_temp} = 'true' ]]; then
          rm -f -r $flag_err_path/*
        fi

      else

        if [[ "$err_index" -gt 5 ]]; then
          if [[ $flag_always_continue = 'false' ]]; then
            printf "\n${B_WARN}[!] Abort testing +5 errors.${E_WARN}\nDo not use --ta flag to always continue."
            clean_temp
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

    if [[ ${flag_out_temp} = 'true' ]]; then
      rm -f -r $flag_out_path/*
    fi
    if [[ ${flag_err_temp} = 'true' ]]; then
      rm -f -r $flag_err_path/*
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
      printf "${B_OK}OK${E_OK}\n"
    fi
  fi

fi

clean_temp
