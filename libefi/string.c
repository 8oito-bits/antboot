#include <libefi.h>

VOID *memcpy(VOID *dest, const VOID *src, UINT64 n)
{
  UINT8 *p = dest;
  const UINT8 *q = src;

  while(n--)
    *p++ = *q++;;

  return dest;
}

UINTN strlen(const CHAR16 *str)
{
  const CHAR16 *p = str - 1;

  while(*++p);

  return p - str;
}
