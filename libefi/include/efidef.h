#ifndef _EFIDEF_INCLUDE_
#define _EFIDEF_INCLUDE_

#include "amd64/efibind.h"
#define VOID  void
#define NULL  ((VOID *) 0)

/* Modifiers for Common UEFI Data Types. */
#define IN
#define OUT
#define OPTIONAL
#define CONST const

typedef UINTN EFI_STATUS;
typedef VOID  *EFI_HANDLE;
typedef VOID  *EFI_EVENT;

/* Characters type. */
typedef UINT16  CHAR16;


// EFI_PHYSICAL_ADDRESS.
typedef UINT64  EFI_PHYSICAL_ADDRESS;

// EFI_VIRTUAL_ADDRESS.
typedef UINT64 EFI_VIRTUAL_ADDRESS;

/* Types used for memory functions. */
typedef enum
{
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress,
  MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum
{
  EfiReservedMemoryType,
  EfiLoaderCode,
  EfiLoaderData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiConventionalMemory,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiPersistentMemory,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct
{
  UINT32                Type;
  EFI_PHYSICAL_ADDRESS  PhysicalStart;
  EFI_VIRTUAL_ADDRESS   VirtualStart;
  UINT64                NumberOfPages;
  UINT64                Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef UINTN EFI_TPL;

// EFI_GUID
typedef struct
{
  UINT32  Data1;
  UINT16  Data2;
  UINT16  Data3;
  UINT8   Data4[8];
} EFI_GUID;

// EFI_RESET_TYPE
typedef enum
{
  EfiResetCold,
  EfiResetWarm,
  EfiResetShutdown,
  EfiResetPlataformSpecific
} EFI_RESET_TYPE;

#endif
