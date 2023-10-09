#include <efi.h>
#include <libefi.h>
#include <file.h>
#include <elf.h>
#include <memory.h>
#include <info.h>
#include <errors.h>

void (*_start_ant)(void);

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
  EFI_STATUS status;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *conout;
  init_lib(image_handle, system_table);

  conout = ST->ConOut;
  status = conout->SetMode(conout, 0);
  if(EFI_ERROR(status))
    error(L"SetMode: Failed to set mode. ");
  
  conout->SetAttribute(conout, EFI_BACKGROUND_BLACK | EFI_WHITE);
  
  EFI_FILE_PROTOCOL *file_protocol; 
  status = file_init_file_protocol(&file_protocol);
  if(EFI_ERROR(status))
    fatal_error(L"fat_init_file_protocol: Failed to init protocol.");
  
  EFI_FILE_PROTOCOL *kfile_interface;
  status = file_open_file(file_protocol, &kfile_interface, L"\\boot\\ant_kernel", EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
  if(EFI_ERROR(status))
    fatal_error(L"fat_open_file: Failed to open file.");

  puts(L"Loading the elf kernel...");

  struct elf kernel_info;
  kernel_info.file_interface = kfile_interface;

  status = elf_parse(&kernel_info);
  if(EFI_ERROR(status))
    fatal_error(L"load_kernel: Failed to parse kernel.");

  status = elf_load_kernel(&kernel_info);
  if(EFI_ERROR(status))
    fatal_error(L"elf_load_kernel: Failed to load kernel.");

  elf_clear_all(&kernel_info);    

  struct gop_video_mode *video_mode;
  video_mode = allocate_runtime_pool(sizeof *video_mode);
  status = gop_init(video_mode);
  if(EFI_ERROR(status))
    fatal_error(L"gop_init: Failed to init gop mode.");

  struct memory_map *map;
  map = allocate_runtime_pool(sizeof *map);
  UINTN map_key;
  status = memory_get_map(map, &map_key);
  if(EFI_ERROR(status))
    fatal_error(L"memory_get_map: Failed to get memory map.");

  status = BS->ExitBootServices(IH, map_key);
  if(EFI_ERROR(status))
    fatal_error(L"ExitBootServices: Failed to exit boot services.");

  _start_ant = (void (*)(void)) kernel_info.elf_header.e_entry;
  _start_ant();

  return EFI_SUCCESS;
}
