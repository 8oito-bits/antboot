#ifndef _PAGE_ALIGN_
#define _PAGE_ALIGN_

#define PAGE 4096

#define ALIGNUP(value, align) ((value) + ((align) - 1) & ~((align) - 1))

#endif
