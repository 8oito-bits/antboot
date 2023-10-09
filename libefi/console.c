#include <libefi.h>

static VOID put(const CHAR16 *);
static VOID puti(INTN);
static INTN put_until_find_percent(const CHAR16 *);
static INTN convert_to_string(va_list vl, const CHAR16 *);

static VOID print_hex(CHAR16 *format, UINT64);

static VOID put(const CHAR16 *string)
{
  ST->ConOut->OutputString(ST->ConOut, (CHAR16 *) string);
}

static VOID puti(INTN number)
{
  CHAR16 string[21] = {0};
  itos(string, number);
  put(string);
}

static INTN put_until_find_percent(const CHAR16 *str)
{
  CHAR16 *p = (CHAR16 *) str;
  INTN result = -1;
  while(*p)
  {
    if(*p == L'%')
    {
      result = p - str;
      break;
    }

    putchar(*p++);
  }

  return result;
}

static VOID print_hex(CHAR16 *format, UINT64 number)
{
  CHAR16 str[17] = {0};
  uitoh(str, number);
  
  while(*format != 'X' && *format != 'x')
  {
    switch(*format++)
    {
      case '#':
        put(L"0x");
        break;
    }

  }
  
  put(str);
}

VOID puts(const CHAR16 *string)
{
  put(string);
  put(L"\n\r");
}

VOID putchar(CHAR16 character)
{
  CHAR16 string[2] = {character, L'\0'};

  ST->ConOut->OutputString(ST->ConOut, string);
}

// Ainda falta terminar
INTN printf(const CHAR16 *format, ...)
{
  va_list vl;

  va_start(vl, format);

  CHAR16 *p = (CHAR16 *) format, *q, c;
  _Bool breakwhile = 0;
  INTN offset = 0;
  while((offset = put_until_find_percent(p)) != -1)
  {
    q = p;
    p += offset;
    
    while(*p && !breakwhile)
    { 
      c = *p++;
      switch(c)
      {
        case 'i':
          puti(va_arg(vl, int));
          breakwhile = 1;
          break;
        case 'c':
          putchar((CHAR16) va_arg(vl, unsigned int));
          breakwhile = 1;
          break;
        case 'x':
          print_hex(q, va_arg(vl, UINT64));
          breakwhile = 1;
          break;
      }
    }

    breakwhile = 0;
  }

  va_end(vl);
  
  return 0;
}
