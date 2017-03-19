#!/bin/bash

while read var assign value; do
  if [[ ${assign} = ':=' ]]; then
    eval ${var//./_}=\"$value\"
  fi
done <./bin/default.config

while read var assign value; do
  if [[ ${assign} = ':=' ]]; then
    eval ${var//./_}=\"$value\"
  fi
done <./build.config

if [[ "$COLOR_SCHEMA" != "" ]]; then
  if [ -s ./bin/colors/${COLOR_SCHEMA}.config ]; then
    COLOR_SCHEMA=./bin/colors/${COLOR_SCHEMA}.config
  fi
  while read var assign value; do
    if [[ ${assign} = ':=' ]]; then
      eval ${var//./_}=\"$value\"
    fi
  done < $COLOR_SCHEMA
fi

red=$COLOR_CODE_RED
green=$COLOR_CODE_GREEN
blue=$COLOR_CODE_BLUE
yellow=$COLOR_CODE_YELLOW
gray=$COLOR_CODE_GRAY
normal=$COLOR_CODE_NORMAL
bold=$COLOR_CODE_BOLD
#cyan="\e[1;36m"
#purple="\e[1;35m"

notation_manual_bold="s/!bold!/$(printf $bold)/i"
notation_manual_error="s/!error!/$(printf $red)/i"
notation_manual_info="s/!info!/$(printf $blue)/i"
notation_manual_warn="s/!warn!/$(printf $yellow)/i"
notation_manual_debug="s/!debug!/$(printf $gray)/i"
notation_manual_good="s/!good!/$(printf $green)/i"
notation_manual_ok="s/!ok!/$(printf $green)/i"
notation_manual_normal="s/!normal!/$(printf $normal)/i"

debug_notificator="s/(\(echo __DEBUG_NOTIFICATOR__ > \/dev\/null\) &)(\s*)(.*)/command: $(printf $blue)\\3$(printf $normal)/i"

notation_bolder="s/(<b>)(.+?)(<\/b>)/$(printf $bold)\\2$(printf $normal)/i"
notation_error="s/(<error>)(.+?)(<\/error>)/$(printf $red)\\2$(printf $normal)/i"
notation_good="s/(<good>)(.+?)(<\/good>)/$(printf $green)\\2$(printf $normal)/i"
notation_info="s/(<info>)(.+?)(<\/info>)/$(printf $blue)\\2$(printf $normal)/i"
notation_warn="s/(<warn>)(.+?)(<\/warn>)/$(printf $yellow)\\2$(printf $normal)/i"
notation_debug="s/(<debug>)(.+?)(<\/debug>)/$(printf $gray)\\2$(printf $normal)/i"
notation_ignore="s/(<ignore>)(.*)//i"
notation_backspace="s/(<del>)/\\x08/igm"
info="s/(^info|^.*[^a-z]info:)/$(printf $blue)\\1$(printf $normal)/i"
error="s/(^error|^.*[^a-z]error:)/$(printf $red)\\1$(printf $normal)/i"
warning="s/(^warning|^.*[^a-z]warning:)/$(printf $yellow)\\1$(printf $normal)/i"
make="s/^make(\[[0-9]+\])?:(.*)//"
make_err="s/(.*)(\*\*\*)(.*)//"
compiler_recipe="s/^((gcc|g\+\+|clang)(.exe)? .*)/$(printf $gray)\\1$(printf $normal)/"

command "make" "--no-print-directory" "--makefile=./bin/build.make" "$@" 2>&1 | sed -ru -e "$debug_notificator" -e "$notation_manual_bold" -e "$notation_manual_error" -e "$notation_manual_info" -e "$notation_manual_warn" -e "$notation_manual_debug" -e "$notation_manual_good" -e "$notation_manual_ok" -e "$notation_manual_normal" -e "$notation_backspace" -e "$notation_ignore" -e "$warning" -e "$error" -e "$info" -e "$notation_bolder" -e "$notation_error" -e "$notation_good" -e "$notation_info" -e "$notation_warn" -e "$notation_debug" -e "$make_err" -e "$make" -e "$compiler_recipe"
