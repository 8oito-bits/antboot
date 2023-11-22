#include <elf.h>
#include <file.h>
#include <align.h>
#include <errors.h>

// Alloc and load program header of elf.
static EFI_STATUS load_program_header(struct elf *elf_info)
{
  EFI_STATUS status;

  UINTN size = elf_info->elf_header.e_phentsize * elf_info->elf_header.e_phnum;
  elf_info->program_header = allocate_boot_pool(size);
  if(elf_info->program_header == NULL)
    return EFI_UNSUPPORTED;

  EFI_FILE_PROTOCOL *file_interface = elf_info->file_interface;
  file_set_position(file_interface, elf_info->elf_header.e_phoff);
  status = file_read_file(file_interface, &size, elf_info->program_header);
  if(EFI_ERROR(status))
    return status;

  return EFI_SUCCESS;
} 

// Alloc and load section header of elf.
static EFI_STATUS load_section_header(struct elf *elf_info)
{
  EFI_STATUS status;

  UINTN size = elf_info->elf_header.e_shentsize * elf_info->elf_header.e_shnum;  
  elf_info->section_header = allocate_boot_pool(size);
  if(elf_info->section_header == NULL)
    return EFI_UNSUPPORTED;

  EFI_FILE_PROTOCOL *file_interface = elf_info->file_interface;
  file_set_position(file_interface, elf_info->elf_header.e_shoff);
  status = file_read_file(file_interface, &size, elf_info->section_header);
  if(EFI_ERROR(status))
    return status;

  return EFI_SUCCESS;
}

// Check if file is an elf.
static INTN is_elf(struct elf *elf_info)
{
  return *((UINT32 *) &elf_info->elf_header.e_ident) == 0x464c457f;
}

EFI_STATUS elf_parse(struct elf *elf_info)
{
  EFI_STATUS status;
  EFI_FILE_PROTOCOL *file_interface = elf_info->file_interface;

  UINTN size = sizeof(struct elf_64_header);
  status = file_read_file(file_interface, &size, &elf_info->elf_header);
  if(EFI_ERROR(status))
    return status;

  if(!is_elf(elf_info))
    return EFI_UNSUPPORTED;

  status = load_program_header(elf_info);
  if(EFI_ERROR(status))
    return status;

  status = load_section_header(elf_info);
  if(EFI_ERROR(status))
    return status;

  return EFI_SUCCESS;
}

VOID elf_clear_all(struct elf *elf_info)
{
  elf_info->file_interface->Close(elf_info->file_interface);
  free_pool(elf_info->program_header);
  free_pool(elf_info->section_header);
}

EFI_STATUS elf_load_kernel(struct elf *elf_info)
{
  EFI_STATUS status;

  UINTN i;
  UINTN size;
  UINTN position;
  EFI_FILE_PROTOCOL *file_interface = elf_info->file_interface;
  EFI_PHYSICAL_ADDRESS address;
  UINT64 p_memsz, p_align;
  EFI_MEMORY_TYPE memory_type;
  for(i = 0; i < elf_info->elf_header.e_phnum; i++)
  {
    if(elf_info->program_header[i].p_type != PT_LOAD)
      continue;

    p_memsz = elf_info->program_header[i].p_memsz;
    p_align = elf_info->program_header[i].p_align;

    if(p_memsz & p_align - 1)
      size = ALIGNUP(p_memsz, p_align);
    else
      size = p_memsz;

    address = elf_info->program_header[i].p_paddr;
    if(elf_info->program_header[i].p_flags & 0x1)
      memory_type = EfiRuntimeServicesCode;
    else
      memory_type = EfiRuntimeServicesData;

    status = BS->AllocatePages(AllocateAddress,
                               memory_type,
                               size / PAGE_SIZE,
                               &address);

    if(EFI_ERROR(status))
    {
      error(L"Failed to alloc page to kernel.");
      return status;
    }

    position = elf_info->program_header[i].p_offset;
    file_set_position(file_interface, position);
    if(file_read_file(file_interface, &size, (EFI_PHYSICAL_ADDRESS *) address))
      return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}
