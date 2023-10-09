#ifndef _INCLUDE_MEMORY_
#define _INCLUDE_MEMORY_

#include <libefi.h>

struct memory_map
{
  UINTN memory_map_size;
  EFI_MEMORY_DESCRIPTOR *memory_descriptor;
  UINTN descriptor_size;
};

EFI_STATUS memory_get_map(struct memory_map *map, UINTN *map_key);

#endif
