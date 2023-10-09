#include <errors.h>

static VOID exit(UINTN status)
{
  BS->Exit(IH, 1, 0, NULL);
}

VOID error(CHAR16 *string)
{
  puts(string);
}

VOID fatal_error(CHAR16 *string)
{
  puts(string);
  exit(1);
}
