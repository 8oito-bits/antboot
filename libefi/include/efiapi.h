#ifndef _EFIAPI_INCLUDE_
#define _EFIAPI_INCLUDE_

#define EFI_SYSTEM_TABLE_REVISION ((2<<16) | (80))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION

typedef struct
{
  UINT64 Signature;
  UINT32 Revision;
  UINT32 HeaderSize;
  UINT32 CRC32;
  UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI Runtime Services.

#define EFI_RUNTIME_SERVICES_SIGNATURE  0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION   EFI_SPECIFICATION_VERSION

// EFI_TIME
typedef struct
{
  UINT16  Year;       // 1900 - 9999
  UINT8   Month;      // 1 - 12
  UINT8   Day;        // 1 - 31
  UINT8   Hour;       // 0 - 23
  UINT8   Minute;     // 0 - 59
  UINT8   Second;     // 0 - 59
  UINT8   Pad1;
  UINT32  Nanosecond; // 0 - 999,999,999
  INT16   TimeZone;   // -1440 to 1440 or 2047
  UINT8   Daylight;
  UINT8   Pad2;
} EFI_TIME;

typedef struct
{
  UINT32  Resolution;
  UINT32  Accuracy;
  BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef
EFI_STATUS
(EFIAPI *EFI_GET_TIME)
(
  OUT EFI_TIME  *Time,
  OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL 
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIME)
(
  IN EFI_TIME *Time
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_WAKEUP_TIME)
(
  OUT BOOLEAN   *Enabled,
  OUT BOOLEAN   *Pending,
  OUT EFI_TIME  *Time 
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WAKEUP_TIME)
(
  IN BOOLEAN Enable,
  IN EFI_TIME *Time OPTIONAL 
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP)
(
  IN UINTN                  MemoryMapSize,
  IN UINTN                  DescriptorSize,
  IN UINT32                 DescriptorVersion,
  IN EFI_MEMORY_DESCRIPTOR  *VirtualMap  
);

typedef
EFI_STATUS
(EFIAPI *EFI_CONVERT_POINTER)
(
  IN UINTN  DebugDisposition,
  IN VOID   **Address 
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_VARIABLE)
(
  IN CHAR16     *VariableName,
  IN EFI_GUID   *VendorGuid,
  OUT UINT32    *Attributes OPTIONAL,
  IN OUT UINTN  *DataSize,
  OUT VOID      *Data OPTIONAL 
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME)
(
  IN OUT UINTN    *VariableNameSize,
  IN OUT CHAR16   *VariableName,
  IN OUT EFI_GUID *VendorGuid 
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_VARIABLE)
(
  IN CHAR16   *VariableName,
  IN EFI_GUID *VendorGuid, 
  IN UINT32   Attributes,
  IN UINTN    DataSize,
  IN VOID     *Data
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT)
(
  OUT UINT32 *HighCount 
);

typedef
EFI_STATUS
(EFIAPI *EFI_RESET_SYSTEM)
(
  IN EFI_RESET_TYPE ResetType,
  IN EFI_STATUS     ResetStatus,
  IN UINTN          DataSize,
  IN VOID           *ResetData OPTIONAL 
);

typedef struct
{
  EFI_GUID  CapsuleGuid;
  UINT32    HeaderSize;
  UINT32    Flags;
  UINT32    CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef
EFI_STATUS
(EFIAPI *EFI_UPDATE_CAPSULE)
(
  IN EFI_CAPSULE_HEADER   **CapsuleHeaderArray,
  IN UINTN                CapsuleCount,
  IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL 
);

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES)
(
  IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
  IN UINTN              CapsuleCount,
  OUT UINT64            *MaximumCapsuleSize,
  OUT EFI_RESET_TYPE    ResetType 
);

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_VARIABLE_INFO)
(
  IN UINT32   Attributes,
  OUT UINT64  *MaximumVariableStorageSize,
  OUT UINT64  *RemainingVariableStorageSize,
  OUT UINT64  *MaximumVariableSize 
);

typedef struct
{
  EFI_TABLE_HEADER                Hdr;

  // Time services.
  EFI_GET_TIME                    GetTime;
  EFI_SET_TIME                    SetTime;  
  EFI_GET_WAKEUP_TIME             GetWakeupTime;
  EFI_SET_WAKEUP_TIME             SetWakeupTime;

  // Virtual Memory Services.
  EFI_SET_VIRTUAL_ADDRESS_MAP     SetVirtualAddressMap;
  EFI_CONVERT_POINTER             ConvertPointer;

  // Variable Services.
  EFI_GET_VARIABLE                GetVariable;
  EFI_GET_NEXT_VARIABLE_NAME      GetNextVariableName;
  EFI_SET_VARIABLE                SetVariable;

  // Miscellaneous Services.
  EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
  EFI_RESET_SYSTEM                ResetSystem;

  // UEFI 2.0 Capsule Services.
  EFI_UPDATE_CAPSULE              UpdateCapsule;
  EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;

  // Miscellaneous UEFI 2.0 Service.
  EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

// EFI Boot Services.
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION  EFI_SPECIFICATION_VERSION

typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL)
(
  IN EFI_TPL NewTpl 
);

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL)
(
  IN EFI_TPL OldTpl 
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES)
(
  IN EFI_ALLOCATE_TYPE        Type,
  IN EFI_MEMORY_TYPE          MemoryType,
  IN UINTN                    Pages,
  IN OUT EFI_PHYSICAL_ADDRESS *Memory 
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES)
(
  IN EFI_PHYSICAL_ADDRESS Memory,
  IN UINTN                Pages 
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP)
(
  IN OUT UINTN                  *MemoryMapSize,
  IN OUT EFI_MEMORY_DESCRIPTOR  *MemoryMap,
  OUT UINTN                     *MapKey,
  OUT UINTN                     *DescriptorSize,
  OUT UINT32                    *DescriptorVersion
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL)
(
  IN EFI_MEMORY_TYPE  PoolType,
  IN UINTN            Size,
  OUT VOID            **Buffer 
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL)
(
  IN VOID *Buffer;
);

typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY)
(
  IN EFI_EVENT  Event,
  IN VOID       *Context
);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT)
(
  IN UINT32           Type,
  IN EFI_TPL          NotifyTpl,
  IN EFI_EVENT_NOTIFY NotifyFunction, OPTIONAL
  IN VOID             *NotifyContext, OPTIONAL
  OUT EFI_EVENT       *Event 
);

typedef enum
{
  TimerCancel,
  TimerPeriodic,
  TimerRelative
} EFI_TIMER_DELAY;

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER)
(
  IN EFI_EVENT        Event,
  IN EFI_TIMER_DELAY  Type,
  IN UINT64           TriggerTime
);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT)
(
  IN UINTN      NumberOfEvents,
  IN EFI_EVENT  *Event,
  OUT UINTN     *Index
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT)
(
  IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT)
(
  IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT)
(
  IN EFI_EVENT Event
);

typedef enum
{
  EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE)
(
  IN OUT EFI_HANDLE     *Handle,
  IN EFI_GUID           *Protocol,
  IN EFI_INTERFACE_TYPE InterfaceType,
  IN VOID               *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE)
(
  IN EFI_HANDLE Handle,
  IN EFI_GUID   *Protocol,
  IN VOID       *OldInterface,
  IN VOID       *NewInterface
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE)
(
  IN EFI_HANDLE Handle,
  IN EFI_GUID   *Protocol,
  IN VOID       *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL)
(
  IN EFI_HANDLE Handle,
  IN EFI_GUID   *Protocol,
  OUT VOID      **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY)
(
  IN EFI_GUID   *Protocol,
  IN EFI_EVENT  Event,
  OUT VOID      **Registration
);

typedef enum
{
  AllHandles,
  ByRegisterNotify,
  ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE)
(
  IN EFI_LOCATE_SEARCH_TYPE SearchType,
  IN EFI_GUID               *Protocol OPTIONAL,
  IN VOID                   *SearchKey OPTIONAL,
  IN OUT UINTN              *BufferSize,
  OUT EFI_HANDLE            *Buffer
);

typedef struct
{
  UINT8 Type;
  UINT8 Subtype;
  UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH)
(
  IN EFI_GUID                     *Protocol,
  IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
  OUT EFI_HANDLE                  *Device
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE)
(
  IN EFI_GUID *Guid,
  IN VOID     *Table
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD)
(
  IN BOOLEAN                  BootPolicy,
  IN EFI_HANDLE               ParentImageHandle,
  IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  IN VOID                     *SourceBuffer OPTIONAL,
  IN UINTN                    SourceSize,
  OUT EFI_HANDLE              *ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START)
(
  IN EFI_HANDLE ImageHandle,
  OUT UINTN     *ExitDataSize,
  OUT CHAR16    **ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT)
(
  IN EFI_HANDLE ImageHandle,
  IN EFI_STATUS ExitStatus,
  IN UINTN      ExitDataSize,
  IN CHAR16     *ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD)
(
  IN EFI_HANDLE ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES)
(
  IN EFI_HANDLE ImageHandle,
  IN UINTN      MapKey
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT)
(
  OUT UINT64  *Count
);

typedef
EFI_STATUS
(EFIAPI *EFI_STALL)
(
  IN UINTN  Microseconds
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER)
(
  IN UINTN  Timeout,
  IN UINT64 WatchdogCode,
  IN UINTN  DataSize,
  IN CHAR16 *WatchdogData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER)
(
  IN EFI_HANDLE               ControllerHandle,
  IN EFI_HANDLE               *DriverImageHandle OPTIONAL,
  IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
  IN BOOLEAN                  Recursive
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER)
(
  IN EFI_HANDLE ControllerHandle,
  IN EFI_HANDLE DriverImageHandle OPTIONAL,
  IN EFI_HANDLE ChildHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL)
(
  IN EFI_HANDLE Handle,
  IN EFI_GUID   *Protocol,
  OUT VOID      **Interface OPTIONAL,
  IN EFI_HANDLE AgentHandle,
  IN EFI_HANDLE ControllerHandle,
  IN UINT32     Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL)
(
  IN EFI_HANDLE Handle,
  IN EFI_GUID   *Protocol,
  IN EFI_HANDLE AgentHandle,
  IN EFI_HANDLE ControllerHandle
);

typedef struct
{
  EFI_HANDLE  AgentHandle;
  EFI_HANDLE  ControllerHandle;
  UINT32      Attributes;
  UINT32      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION)
(
  IN EFI_HANDLE                           Handle,
  IN EFI_GUID                             *Protocol,
  OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
  OUT UINTN                               *EntryCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE)
(
  IN EFI_HANDLE Handle,
  OUT EFI_GUID  ***ProtocolBuffer,
  OUT UINTN     *ProtocolBufferCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER)
(
  IN EFI_LOCATE_SEARCH_TYPE SearchType,
  IN EFI_GUID               *Protocol OPTIONAL,
  IN VOID                   *SearchKey OPTIONAL,
  IN OUT UINTN              *NoHandles,
  OUT EFI_HANDLE            **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL)
(
  IN EFI_GUID *Protocol,
  IN VOID     *Registration OPTIONAL,
  OUT VOID    **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)
(
  IN OUT EFI_HANDLE *Handle,
  ...
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)
(
  IN EFI_HANDLE Handle,
  ...
);

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32)
(
  IN VOID     *Data,
  IN UINTN    DataSize,
  OUT UINT32  *Crc32
);

typedef
VOID
(EFIAPI *EFI_COPY_MEM)
(
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINTN  Length
);

typedef
VOID
(EFIAPI *EFI_SET_MEM)
(
  IN VOID   *Buffer,
  IN UINTN  Size,
  IN UINT8  Value
);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX)
(
  IN UINT32     Type,
  IN EFI_TPL    NotifyTpl,
  IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
  IN CONST VOID       *NotifyContext OPTIONAL,
  IN CONST EFI_GUID   *EventGroup OPTIONAL,
  OUT EFI_EVENT       *Event
);

typedef struct
{
  EFI_GUID  VendorGuid;
  VOID      *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct
{
  EFI_TABLE_HEADER                  Hdr;

  // Task Priority Services.
  EFI_RAISE_TPL                     RaiseTPL;
  EFI_RESTORE_TPL                   RestoreTPL;

  // Memory Services
  EFI_ALLOCATE_PAGES                AllocatePages;
  EFI_FREE_PAGES                    FreePages;
  EFI_GET_MEMORY_MAP                GetMemoryMap;
  EFI_ALLOCATE_POOL                 AllocatePool;
  EFI_FREE_POOL                     FreePool;

  // Event & Timer Services.
  EFI_CREATE_EVENT                  CreateEvent;
  EFI_SET_TIMER                     SetTimer;
  EFI_WAIT_FOR_EVENT                WaitForEvent;
  EFI_SIGNAL_EVENT                  SignalEvent;
  EFI_CLOSE_EVENT                   CloseEvent;
  EFI_CHECK_EVENT                   CheckEvent;

  // Protocol Handler Services.
  EFI_INSTALL_PROTOCOL_INTERFACE    InstallProtocolInterface; 
  EFI_REINSTALL_PROTOCOL_INTERFACE  ReinstallProtocolInterface;
  EFI_UNINSTALL_PROTOCOL_INTERFACE  UninstallProtocolInterface;
  EFI_HANDLE_PROTOCOL               HandleProtocol;
  VOID                              *Reserved;
  EFI_REGISTER_PROTOCOL_NOTIFY      RegisterProtocolNotify;
  EFI_LOCATE_HANDLE                 LocateHandle;  
  EFI_LOCATE_DEVICE_PATH            LocateDevicePath;
  EFI_INSTALL_CONFIGURATION_TABLE   InstallConfigurationTable;
  
  // Image Services.
  EFI_IMAGE_LOAD                    LoadImage;
  EFI_IMAGE_START                   StartImage;
  EFI_EXIT                          Exit;
  EFI_IMAGE_UNLOAD                  UnloadImage;
  EFI_EXIT_BOOT_SERVICES            ExitBootServices;

  // Miscellaneous Services.
  EFI_GET_NEXT_MONOTONIC_COUNT      GetNextMonotonicCount;
  EFI_STALL                         Stall;
  EFI_SET_WATCHDOG_TIMER            SetWatchdogTimer;
  
  // DriverSupport Services.
  EFI_CONNECT_CONTROLLER            ConnectController;
  EFI_DISCONNECT_CONTROLLER         DisconnectController;

  // Open and Close Protocol Services.
  EFI_OPEN_PROTOCOL                 OpenProtocol;
  EFI_CLOSE_PROTOCOL                CloseProtocol;
  EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation;

  // Library Services.
  EFI_PROTOCOLS_PER_HANDLE          ProtocolsPerHandle;
  EFI_LOCATE_HANDLE_BUFFER          LocateHandleBuffer;
  EFI_LOCATE_PROTOCOL               LocateProtocol;
  EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES
    InstallMultipleProtocolInterfaces;
  EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES
    UninstallMultipleProtocolInterfaces;

  // 32-bit CRC Services.
  EFI_CALCULATE_CRC32               CalculateCrc32;

  // Miscellaneous Services.
  EFI_COPY_MEM                      CopyMem;
  EFI_SET_MEM                       SetMem;
  EFI_CREATE_EVENT_EX               CreateEventEx;
} EFI_BOOT_SERVICES;

typedef struct
{
  EFI_TABLE_HEADER                Hdr;
  CHAR16                          *FirmwareVendor;
  UINT32                          FirmwareRevision;
  EFI_HANDLE                      ConsoleHandle;  
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *ConIn;  
  EFI_HANDLE                      ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
  EFI_HANDLE                      StandardErrorHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
  EFI_RUNTIME_SERVICES            *RuntimeServices;
  EFI_BOOT_SERVICES               *BootServices;
  UINTN                           NumberOfTableEntries;
  EFI_CONFIGURATION_TABLE         *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
