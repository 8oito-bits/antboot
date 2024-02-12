#ifndef _ALIGN_INCLUDE_
#define _ALIGN_INCLUDE_

#define PAGE 4096

#define ALIGNUP(value, align) ((value) + ((align) - 1) & ~((align) - 1))

#endif
