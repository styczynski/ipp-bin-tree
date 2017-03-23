#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


void debugInfo(const char* format, const char* format_prepend, ...) {
  char format_new[100];
  strcpy (format_new, "~ ");
  strcpy (format_new, format_prepend);
  strcat (format_new, format);
  strcat (format_new, "\n");

  va_list arg;

  va_start (arg, format_prepend);
  printf(format_new, arg);
  fflush(stdout);
  va_end (arg);
}
