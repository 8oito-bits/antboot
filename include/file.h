#ifndef _DEFINE_FAT_
#define _DEFINE_FAT_

#include <libefi.h>

EFI_STATUS file_init_file_protocol(EFI_FILE_PROTOCOL **);
EFI_STATUS file_open_file(EFI_FILE_PROTOCOL *,
                          EFI_FILE_PROTOCOL **,
                          CHAR16 *,
                          UINT64,
                          UINT64);
EFI_STATUS file_close_file(EFI_FILE_PROTOCOL *);
EFI_STATUS file_read_file(EFI_FILE_PROTOCOL *,
                          UINTN *,
                          VOID *);
EFI_STATUS file_set_position(EFI_FILE_PROTOCOL *,
                             UINT64);
#endif
