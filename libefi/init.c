#include <efi.h>
#include <libefi.h>

EFI_SYSTEM_TABLE *ST;
EFI_HANDLE IH;
EFI_BOOT_SERVICES *BS;
EFI_RUNTIME_SERVICES *RS;

VOID init_lib(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  ST = system_table;
  IH = image_handle;
  BS = ST->BootServices;
  RS = ST->RuntimeServices;
}
