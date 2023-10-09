#ifndef _INCLUDE_INFO_
#define _INCLUDE_INFO_

#include <libefi.h>
#include <memory.h>
#include <gop.h>

struct boot_info
{
  struct memory_map *map;    
  struct gop_video_mode mode;
};

#endif
