#include <libefi.h>

VOID *allocate_pool(UINTN size, EFI_MEMORY_TYPE type)
{
  VOID *buffer;
  EFI_STATUS status;

  status = BS->AllocatePool(type, size, &buffer);

  if(status != EFI_SUCCESS)
    return NULL;

  return buffer;
}

VOID *allocate_runtime_pool(UINTN size)
{
  return allocate_pool(size, EfiRuntimeServicesData);
}

VOID *allocate_boot_pool(UINTN size)
{
  return allocate_pool(size, EfiBootServicesData);
}

VOID free_pool(VOID *buffer)
{
  BS->FreePool(buffer);
}
