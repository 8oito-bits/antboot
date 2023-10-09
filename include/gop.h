#ifndef _INCLUDE_GOP_
#define _INCLUDE_GOP_

#include <libefi.h>

struct gop_video_mode
{
  VOID                      *frame_buffer_base;
  UINT64                    frame_buffer_size;
  UINT32                    horizontal_resolution;
  UINT32                    vertical_resolution;
  EFI_GRAPHICS_PIXEL_FORMAT pixel_format;
};

EFI_STATUS gop_init(struct gop_video_mode *);

#endif
