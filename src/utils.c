/*
*  Various utilities. (C99 standard)
*
*  MIT LICENSE
*  @Piotr Styczyński 2017
*/
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*
* Print debug info to stdio.
* Works as printf(format + format_prepend, ...)
* Use as printf:
*    debugInfo("%d", ", %d", 42, 42); // -> Output: 42, 42
*
*/
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
