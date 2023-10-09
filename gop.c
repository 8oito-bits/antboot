#include <gop.h>

// Init video mode.
EFI_STATUS gop_init(struct gop_video_mode *video_mode)
{
  EFI_STATUS status;

  EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *gop_interface;
  status = BS->LocateProtocol(&gop_guid, NULL, (VOID **) &gop_interface);
  if(EFI_ERROR(status))
    return status;

  UINTN size_of_info;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
  status = gop_interface->QueryMode(gop_interface, 0, &size_of_info, &info);
  if(EFI_ERROR(status))
    return status;

  status = gop_interface->SetMode(gop_interface, 0);
  if(EFI_ERROR(status))
    return status;

  video_mode->frame_buffer_base = (void *) gop_interface->Mode->FrameBufferBase;
  video_mode->frame_buffer_size = gop_interface->Mode->FrameBufferSize;
  video_mode->horizontal_resolution = info->HorizontalResolution;
  video_mode->vertical_resolution = info->VerticalResolution;
  video_mode->pixel_format = info->PixelFormat;

  return EFI_SUCCESS; 
}
