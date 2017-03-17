#!/bin/bash

red="\e[1;31m"
green="\e[1;32m"
blue="\e[1;34m"
cyan="\e[1;36m"
purple="\e[1;35m"
yellow="\e[1;33m"
gray="\e[1;30m"
normal="\e[0m"
bold=" \e[1m"
backspace="\b"

notation_manual_bold="s/!bold!/$(printf $bold)/i"
notation_manual_error="s/!error!/$(printf $red)/i"
notation_manual_info="s/!info!/$(printf $blue)/i"
notation_manual_warn="s/!warn!/$(printf $yellow)/i"
notation_manual_debug="s/!debug!/$(printf $gray)/i"
notation_manual_good="s/!good!/$(printf $green)/i"
notation_manual_normal="s/!normal!/$(printf $normal)/i"

notation_bolder="s/(<b>)(.+?)(<\/b>)/$(printf $bold)\\2$(printf $normal)/i"
notation_error="s/(<error>)(.+?)(<\/error>)/$(printf $red)\\2$(printf $normal)/i"
notation_good="s/(<good>)(.+?)(<\/good>)/$(printf $green)\\2$(printf $normal)/i"
notation_info="s/(<info>)(.+?)(<\/info>)/$(printf $blue)\\2$(printf $normal)/i"
notation_warn="s/(<warn>)(.+?)(<\/warn>)/$(printf $yellow)\\2$(printf $normal)/i"
notation_debug="s/(<debug>)(.+?)(<\/debug>)/$(printf $gray)\\2$(printf $normal)/i"
notation_ignore="s/(<ignore>)(.*)//i"
notation_backspace="s/(<del>)/\\x08/igm"
error="s/(^error|^.*[^a-z]error:)/$(printf $red)\\1$(printf $normal)/i"
warning="s/(^warning|^.*[^a-z]warning:)/$(printf $yellow)\\1$(printf $normal)/i"
make="s/^make(\[[0-9]+\])?:(.*)//"
make_err="s/(.*)(\*\*\*)(.*)//"
compiler_recipe="s/^((gcc|g\+\+|clang)(.exe)? .*)/$(printf $gray)\\1$(printf $normal)/"

command "make" "--no-print-directory" "--makefile=./bin/build.make" "$@" 2>&1 | sed -ru -e "$notation_manual_bold" -e "$notation_manual_error" -e "$notation_manual_info" -e "$notation_manual_warn" -e "$notation_manual_debug" -e "$notation_manual_good" -e "$notation_manual_normal" -e "$notation_backspace" -e "$notation_ignore" -e "$warning" -e "$error" -e "$notation_bolder" -e "$notation_error" -e "$notation_good" -e "$notation_info" -e "$notation_warn" -e "$notation_debug" -e "$make_err" -e "$make" -e "$compiler_recipe"
