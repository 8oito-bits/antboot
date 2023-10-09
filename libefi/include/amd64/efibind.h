#ifndef _EFIBIND_INCLUDE_
#define _EFIBIND_INCLUDE_

#define EFIAPI __attribute__((ms_abi))

// Common UEFI Data Types.
typedef unsigned char           UINT8;
typedef unsigned short          UINT16;
typedef unsigned int            UINT32;
typedef unsigned long long int  UINT64;
typedef UINT64                  UINTN;

typedef char          INT8;
typedef short         INT16;
typedef int           INT32;
typedef long long int INT64;
typedef INT64         INTN;

typedef INT8 BOOLEAN;

typedef UINT64 EFI_LBA;

#define INTERFACE_DECL(x) struct x

#endif
