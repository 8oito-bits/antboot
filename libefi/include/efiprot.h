#ifndef _EFIPROT_INCLUDE_
#define _EFIPROT_INCLUDE_

/*
 *=============================
 * Efi Disk IO Protocol.
 *=============================
 */
INTERFACE_DECL(_EFI_DISK_IO_PROTOCOL);

#define EFI_DISK_IO_PROTOCOL_GUID \
  {0xCE345171,0xBA0B,0x11d2, {0x8e,0x4F,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ)
(
  IN struct _EFI_DISK_IO_PROTOCOL *This,
  IN UINT32                       MediaID,
  IN UINT64                       Offset,
  IN UINTN                        BufferSize,
  OUT VOID                        *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE)
(
  IN struct _EFI_DISK_IO_PROTOCOL *This,
  IN UINT32                       MediaID,
  IN UINT64                       Offset,
  IN UINTN                        BufferSize,
  OUT VOID                        *Buffer
);

typedef struct _EFI_DISK_IO_PROTOCOL
{
  UINT64          Revision;
  EFI_DISK_READ   ReadDisk;
  EFI_DISK_WRITE  WriteDisk;
} EFI_DISK_IO_PROTOCOL;

/*
 *=============================
 * Efi Block IO Protocol.
 *=============================
 */
INTERFACE_DECL(_EFI_BLOCK_IO_PROTOCOL);

#define EFI_BLOCK_IO_PROTOCOL_GUID \
  {0x964e5b21,0x6459,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}


#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2 << 16) | (31))

typedef struct
{
  UINT32  MediaId;
  BOOLEAN RemovableMedia;
  BOOLEAN MediaPresent;
  BOOLEAN LogicalPartition;
  BOOLEAN ReadOnly;
  BOOLEAN WriteCaching;
  UINT32  BlockSize;
  UINT32  IoAlign;
  EFI_LBA LastBlock;
  EFI_LBA LowestAlignedLba;
  UINT32  LogicalBlocksPerPhysicalBlock;
  UINT32  OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET)
(
  IN struct _EFI_BLOCK_IO_PROTOCOL *This,
  IN BOOLEAN                       ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ)
(
  IN struct _EFI_BLOCK_IO_PROTOCOL  *This, 
  IN UINT32                         MediaId,
  IN EFI_LBA                        LBA,
  IN UINTN                          BufferSize,
  OUT VOID                          *Buffer
);


typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE)
(
  IN struct _EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                         MediaId,
  IN EFI_LBA                        LBA,
  IN UINTN                          BufferSize,
  OUT VOID                          *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH)
(
  IN struct _EFI_BLOCK_IO_PROTOCOL *This
);

typedef struct _EFI_BLOCK_IO_PROTOCOL
{
  UINT64              Revision;
  EFI_BLOCK_IO_MEDIA  *Media;
  EFI_BLOCK_RESET     Reset;
  EFI_BLOCK_READ      ReadBlocks;
  EFI_BLOCK_WRITE     WriteBlocks;
  EFI_BLOCK_FLUSH     FLushBlocks;
} EFI_BLOCK_IO_PROTOCOL;
/*
 *=============================
 * Efi File Protocol.
 *=============================
 */
INTERFACE_DECL(_EFI_FILE_PROTOCOL);

#define EFI_FILE_PROTOCOL_REVISION        0x00010000
#define EFI_FILE_PROTOCOL_REVISION2       0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

// Open Modes
#define EFI_FILE_MODE_READ    0x0000000000000001
#define EFI_FILE_MODE_WRITE   0x0000000000000002
#define EFI_FILE_MODE_CREATE  0x8000000000000000

// File Attributes
#define EFI_FILE_READ_ONLY  0x0000000000000001
#define EFI_FILE_HIDDEN     0x0000000000000002
#define EFI_FILE_SYSTEM     0x0000000000000004
#define EFI_FILE_RESERVED   0x0000000000000008
#define EFI_FILE_DIRECTORY  0x0000000000000010
#define EFI_FILE_ARCHIVE    0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037


typedef struct
{
  EFI_EVENT   Event;
  EFI_STATUS  Status;
  UINTN       BufferSize;
  VOID        *Buffer;
} EFI_FILE_IO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  OUT struct _EFI_FILE_PROTOCOL **NewHandle,
  IN CHAR16                     *FileName,
  IN UINT64                     OpenMode,
  IN UINT64                     Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE)
(
  IN struct _EFI_FILE_PROTOCOL  *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE)
(
  IN struct _EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN OUT UINTN                  *BufferSize,
  OUT VOID                      *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN OUT UINTN                  *BufferSize,
  IN VOID                       *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  OUT UINT64                    *Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN UINT64                     Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN EFI_GUID                   *InformationType,
  IN OUT UINTN                  *BufferSize,
  OUT VOID                      *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN EFI_GUID                   *InformationType,
  IN UINTN                      BufferSize,
  IN VOID                       *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH)
(
  IN struct _EFI_FILE_PROTOCOL  *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  OUT struct _EFI_FILE_PROTOCOL **NewHandle,
  IN CHAR16                     *FileName,
  IN UINT64                     OpenMode,
  IN UINT64                     Attributes,
  IN OUT EFI_FILE_IO_TOKEN      *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ_EX)
(
  IN struct _EFI_FILE_PROTOCOL      *This,
  IN OUT EFI_FILE_IO_TOKEN          *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE_EX)
(
  IN struct _EFI_FILE_PROTOCOL  *This,
  IN OUT EFI_FILE_IO_TOKEN      *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX)
(
  IN struct _EFI_FILE_PROTOCOL      *This,
  IN OUT EFI_FILE_IO_TOKEN          *Token
);

typedef struct _EFI_FILE_PROTOCOL
{
  UINT64                Revision;
  EFI_FILE_OPEN         Open;
  EFI_FILE_CLOSE        Close;
  EFI_FILE_DELETE       Delete;
  EFI_FILE_READ         Read;
  EFI_FILE_WRITE        Write;
  EFI_FILE_GET_POSITION GetPosition;
  EFI_FILE_SET_POSITION SetPosition;
  EFI_FILE_GET_INFO     GetInfo;
  EFI_FILE_SET_INFO     SetInfo;
  EFI_FILE_FLUSH        Flush;
  EFI_FILE_OPEN_EX      OpenEx;
  EFI_FILE_READ_EX      ReadEx;
  EFI_FILE_WRITE_EX     WriteEx;
  EFI_FILE_FLUSH_EX     FlushEx;
} EFI_FILE_PROTOCOL;


/*
 *=============================
 * Efi Simple File System Protocol.
 *=============================
 */
INTERFACE_DECL(_EFI_SIMPLE_FILE_SYSTEM_PROTOCOL);

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
  {0x0964e5b22,0x6459,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)
(
  IN struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *This,
  OUT EFI_FILE_PROTOCOL                       **Root 
);

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
{
  UINT64                                      Revision;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

#endif
