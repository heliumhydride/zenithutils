#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../include/elf.h"
#include "../include/pe.h"
#include "../config.h"

enum formats {
  FMT_AUTO,
  FMT_ELF,
  FMT_PE,
  FMT_UNKNOWN
};

int valid_elf_magic(uint8_t* buf);
int valid_pe_magic(uint8_t* buf);
void print_elf_info(uint8_t* buf);
void print_pe_info(uint8_t* buf);

void print_usage(char* program) {
  fprintf(stderr, "usage: %s executable [...]\n", program);
}

int main(int argc, char* argv[]) {
  char* program = argv[0];

  int exefmt = FMT_AUTO;
  if(argc < 2) {
    print_usage(program);
    return 1;
  }

  int multiple_files = 0;
  if(argc > 2)
    multiple_files = 1;

  putchar('\n');

  while(*++argv) {
    FILE* fp = fopen(*argv, "rb");
    if(fp == NULL) {
      print_error("%s: %s: could not open file", program, *argv);
      return 1;
    }

    // Read entire file into memory
    size_t filesize = (size_t)get_filesize(fp);
    uint8_t* buf = malloc(filesize);
    if(buf == NULL) {
      print_error("%s: malloc() failed", program);
      return 2;
    }
    fread(buf, filesize, 1, fp);
    fclose(fp);

    // Autodetect
    if(valid_elf_magic(buf)) {
      exefmt = FMT_ELF;
    } else if(valid_pe_magic(buf)) {
      exefmt = FMT_PE;
    } else {
      print_error("%s: could not autodetect format for '%s'", program, *argv);
      free(buf);
      return 1;
    }

    if(multiple_files)
      printf("%s:\n", *argv);

    // Dispatch accordingly
    switch(exefmt) {
      case FMT_ELF:
        print_elf_info(buf);
        break;
      case FMT_PE:
        print_pe_info(buf);
        break;
    }

    puts(ANSI_NORM);
    free(buf);
  }
  return 0;
}

int valid_elf_magic(uint8_t* buf) {
  char magic_buf[5];
  memcpy(magic_buf, buf, 4);
  magic_buf[4] = '\0';
  return(!strcmp(ELF_MAGIC, magic_buf));
}

int valid_pe_magic(uint8_t* buf) {
  DosStub_t* dos_stub = (DosStub_t*)buf;
  if(dos_stub->Magic != 0x5a4d)
    return 0;

  uintptr_t pe_offset = dos_stub->e_lfanew;
  PeHeader_t* pe = (PeHeader_t*)(buf + pe_offset);

  return(pe->Magic == 0x00004550);
}

void print_elf_info(uint8_t* buf) {
  puts(EXEDUMP_COLOR1"  Format:       "EXEDUMP_COLOR2"ELF");

  Elf64_Ehdr* elf64 = (Elf64_Ehdr*)buf;
  Elf32_Ehdr* elf32 = (Elf32_Ehdr*)buf;

  // For the elf identifiers, we can assume an architecture, as both are the same size in elf32 and elf64
  printf(EXEDUMP_COLOR1"  Bitness:      "EXEDUMP_COLOR2);
  uint8_t bitness = elf32->e_ident[4]; // needed for later
  switch(bitness) {
    case ELF_BITS_32:
      puts("32");
      break;
    case ELF_BITS_64:
      puts("64");
      break;
    default:
      puts("?");
  }

  printf(EXEDUMP_COLOR1"  Endianness:   "EXEDUMP_COLOR2);
  uint8_t endianness = elf32->e_ident[5]; // also needed for later
  switch(endianness) {
    case ELF_LSB:
      puts("Little (LSB)");
      break;
    case ELF_MSB:
      puts("Big (MSB)");
      break;
    default:
      puts("?");
  }

  printf(EXEDUMP_COLOR1"  OS:           "EXEDUMP_COLOR2);
  switch(elf32->e_ident[7]) {
    case ABI_SYSV:
      puts("SysV");
      break;
    case ABI_HPUX:
      puts("HP-UX");
      break;
    case ABI_NETBSD:
      puts("NetBSD");
      break;
    case ABI_LINUX:
      puts("Linux");
      break;
    case ABI_HURD:
      puts("GNU/Hurd");
      break;
    case ABI_86OPEN:
      puts("86Open");
      break;
    case ABI_SOLARIS:
      puts("Solaris");
      break;
    case ABI_AIX:
      puts("AIX");
      break;
    case ABI_IRIS:
      puts("IRIS");
      break;
    case ABI_FREEBSD:
      puts("FreeBSD");
      break;
    case ABI_TRU64:
      puts("Tru64");
      break;
    case ABI_MODESTO:
      puts("Modesto");
      break;
    case ABI_OPENBSD:
      puts("OpenBSD");
      break;
    case ABI_ARM_AEABI:
      puts("ARM EABI");
      break;
    case ABI_ARM:
      puts("ARM");
      break;
    case ABI_STANDALONE:
      puts("Standalone");
      break;
    default:
      puts("?");
  }

  printf(EXEDUMP_COLOR1"  Machine:      "EXEDUMP_COLOR2);
  uint16_t machine = elf64->e_machine;
  if(bitness == ELF_BITS_32) machine = elf32->e_machine;
  if(endianness == ELF_MSB)  machine = reverse_end16(machine);
  switch(machine) {
    case EM_NONE:
      puts("None");
      break;
    case EM_SPARC:
      puts("Sparc");
      break;
    case EM_386:
      puts("i386");
      break;
    case EM_68K:
      puts("Motorola M68K");
      break;
    case EM_MIPS:
      puts("MIPS");
      break;
    case EM_MIPS_RS3_LE:
      puts("MIPS Little Endian");
      break;
    case EM_PPC:   // fall
    case EM_PPC64:
      puts("PowerPC");
      break;
    case EM_S390:
      puts("IBM S390");
      break;
    case EM_ARM:
      puts("ARM");
      break;
    case EM_SH:
      puts("Hitachi SH4");
      break;
    case EM_SPARCV9:
      puts("Sparc V9");
      break;
    case EM_IA_64:
      puts("Itanium 64");
      break;
    case EM_X86_64:
      puts("x86_64");
      break;
    case EM_AVR:
      puts("AVR");
      break;
    case EM_AARCH64:
      puts("AArch64");
      break;
    case EM_CUDA:
      puts("Nvidia CUDA");
      break;
    case EM_AMDGPU:
      puts("AMD GPU");
      break;
    case EM_RISCV:
      puts("RISC-V");
      break;
    case EM_LOONG:
      puts("Loongarch");
      break;
    default:
      puts("Unknown");
  }

  uint32_t phoff32 = elf32->e_phoff;
  uint64_t phoff64 = elf64->e_phoff;
  if(endianness == ELF_MSB) {
    phoff32 = reverse_end32(phoff32);
    phoff64 = reverse_end64(phoff64);
  }
  Elf32_Phdr* phdr32 = (Elf32_Phdr*)(buf + phoff32);
  Elf64_Phdr* phdr64 = (Elf64_Phdr*)(buf + phoff64);

  uint16_t phnum = elf64->e_phnum;
  if(bitness == ELF_BITS_32) phnum = elf32->e_phnum;
  if(endianness == ELF_MSB)  phnum = reverse_end16(phnum);
  printf(EXEDUMP_COLOR1"  Headers:      "EXEDUMP_COLOR2"%d\n", phnum);

  int is_dyn_and_exec = 0;
  char* interp = NULL;
  for(int i = 0; i < phnum; i++) {
    uint32_t type = phdr64->p_type;
    if(bitness == ELF_BITS_32) type = phdr32->p_type;
    if(endianness == ELF_MSB)  type = reverse_end32(type);

    uint32_t offset32 = phdr32->p_offset;
    uint64_t offset64 = phdr64->p_offset;
    if(endianness == ELF_MSB) {
      if(bitness == ELF_BITS_32)
        offset32 = reverse_end32(offset32);
      else
        offset64 = reverse_end64(offset64);
    }

    if(type == 3) {
      is_dyn_and_exec = 1;
      if(bitness == ELF_BITS_32)
        interp = (char*)(buf + offset32);
      else
        interp = (char*)(buf + offset64);
    }

    uint16_t phentsize = elf64->e_phentsize;
    if(bitness == ELF_BITS_32) phentsize = elf32->e_phentsize;
    if(endianness == ELF_MSB)  phentsize = reverse_end16(phentsize);
    phdr64 = (Elf64_Phdr*)((uint8_t*)phdr64 + phentsize);
    phdr32 = (Elf32_Phdr*)((uint8_t*)phdr32 + phentsize);
  }

  printf(EXEDUMP_COLOR1"  Type:         "EXEDUMP_COLOR2);
  uint16_t type = elf64->e_type;
  if(bitness == ELF_BITS_32) type = elf32->e_type;
  if(endianness == ELF_MSB)  type = reverse_end16(type);
  switch(type) {
    case ET_REL:
      puts("Relocatable");
      break;
    case ET_EXEC:
      puts("Executable");
      break;
    case ET_DYN:
      if(is_dyn_and_exec)
        puts("Dynamic executable");
      else
        puts("Shared library");
      break;
    case ET_CORE:
      puts("Core dump");
      break;
    default:
      puts("Unknown");
  }

  if(is_dyn_and_exec)
    printf(EXEDUMP_COLOR1"  Interpreter:  "EXEDUMP_COLOR2"%s\n", interp);
}

void print_pe_info(uint8_t* buf) {
  puts(EXEDUMP_COLOR1"  Format:             "EXEDUMP_COLOR2"PE");

  DosStub_t* dos_stub = (DosStub_t*)buf;
  uintptr_t pe_offset = dos_stub->e_lfanew;
  PeHeader_t* pe = (PeHeader_t*)(buf + pe_offset);

  printf(EXEDUMP_COLOR1"  Machine:            "EXEDUMP_COLOR2);
  switch(pe->Machine) {
    case IMAGE_FILE_MACHINE_UNKNOWN:
      puts("N/A");
      break;
    case IMAGE_FILE_MACHINE_ALPHA:
      puts("Alpha 32");
      break;
    case IMAGE_FILE_MACHINE_ALPHA64:
      puts("Alpha 64");
      break;
    case IMAGE_FILE_MACHINE_AM33:
      puts("Matsushita AM33");
      break;
    case IMAGE_FILE_MACHINE_AMD64:
      puts("AMD64");
      break;
    case IMAGE_FILE_MACHINE_ARM:
      puts("ARM");
      break;
    case IMAGE_FILE_MACHINE_ARM64:
      puts("ARM64");
      break;
    case IMAGE_FILE_MACHINE_ARM64EC:
      puts("ARM64 (Emulation Compatible)");
      break;
    case IMAGE_FILE_MACHINE_ARM64X:
      puts("Combined ARM64/ARM64EC");
      break;
    case IMAGE_FILE_MACHINE_ARMNT:
      puts("ARM (Thumb-2)");
      break;
    case IMAGE_FILE_MACHINE_EBC:
      puts("EFI Byte code");
      break;
    case IMAGE_FILE_MACHINE_I386:
      puts("Intel x86");
      break;
    case IMAGE_FILE_MACHINE_IA64:
      puts("Intel Itanium 64");
      break;
    case IMAGE_FILE_MACHINE_M32R:
      puts("Mitsubishi M32R");
      break;
    case IMAGE_FILE_MACHINE_MIPS16:
      puts("MIPS 16");
      break;
    case IMAGE_FILE_MACHINE_MIPSFPU:
      puts("MIPS (w/ FPU)");
      break;
    case IMAGE_FILE_MACHINE_MIPSFPU16:
      puts("MIPS16 (w/ FPU)");
      break;
    case IMAGE_FILE_MACHINE_POWERPC:
      puts("PowerPC");
      break;
    case IMAGE_FILE_MACHINE_POWERPCFP:
      puts("PowerPC (w/ float support)");
      break;
    case IMAGE_FILE_MACHINE_R4000:
      puts("MIPS little endian");
      break;
    case IMAGE_FILE_MACHINE_RISCV32:
      puts("RISC-V 32");
      break;
    case IMAGE_FILE_MACHINE_RISCV64:
      puts("RISC-V 64");
      break;
    case IMAGE_FILE_MACHINE_RISCV128 :
      puts("RISC-V 128");
      break;
    case IMAGE_FILE_MACHINE_SH3:
      puts("Hitachi SH3");
      break;
    case IMAGE_FILE_MACHINE_SH3DSP:
      puts("Hitachi SH3 DSP");
      break;
    case IMAGE_FILE_MACHINE_SH4:
      puts("Hitachi SH4");
      break;
    case IMAGE_FILE_MACHINE_SH5:
      puts("Hitachi SH5");
      break;
    case IMAGE_FILE_MACHINE_THUMB:
      puts("Thumb");
      break;
    case IMAGE_FILE_MACHINE_WCEMIPSV2:
      puts("MIPS little endian WCE v2");
      break;
    default:
      puts("Unknown");
  }

  printf(EXEDUMP_COLOR1"  Number of Sectors:  "EXEDUMP_COLOR2"%d\n", pe->NumberOfSections);

  printf(EXEDUMP_COLOR1"  Characteristics:    "EXEDUMP_COLOR2);
  if(pe->Characteristics & IMAGE_FILE_RELOCS_STRIPPED)
    printf("relocs_stripped ");
  if(pe->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE)
    printf("executable ");
  if(pe->Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE)
    printf("large_address_aware ");
  if(pe->Characteristics & IMAGE_FILE_32BIT_MACHINE)
    printf("32bit ");
  if(pe->Characteristics & IMAGE_FILE_DEBUG_STRIPPED)
    printf("debug_stripped ");
  if(pe->Characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP)
    printf("removable_run_from_swap ");
  if(pe->Characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP)
    printf("net_run_from_swap ");
  if(pe->Characteristics & IMAGE_FILE_SYSTEM)
    printf("system ");
  if(pe->Characteristics & IMAGE_FILE_DLL)
    printf("dll ");
  if(pe->Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY)
    printf("uniprocessor_only ");
  putchar('\n');

  int is_pe_plus = 0;
  Pe32OptHeader_t* pe_opt = (Pe32OptHeader_t*)((uint8_t*)pe + sizeof(PeHeader_t));
  Pe32PlusOptHeader_t* peplus_opt;
  if(pe_opt->Magic == 0x20b) {
    is_pe_plus = 1;
    peplus_opt = (Pe32PlusOptHeader_t*)pe_opt;
  }

  printf(EXEDUMP_COLOR1"  PE Type:            "EXEDUMP_COLOR2"PE32%c\n", is_pe_plus ? '+' : ' ');

  printf(EXEDUMP_COLOR1"  Entry at:           "EXEDUMP_COLOR2);
  if(is_pe_plus)
    printf("0x%x", peplus_opt->AddressOfEntryPoint);
  else
    printf("0x%x", pe_opt->AddressOfEntryPoint);
  putchar('\n');

  printf(EXEDUMP_COLOR1"  OS Version:         "EXEDUMP_COLOR2);
  if(is_pe_plus) {
    printf("%d.%d",
      peplus_opt->MajorOperatingSystemVersion,
      peplus_opt->MinorOperatingSystemVersion
    );
  }
  else {
    printf("%d.%d",
      pe_opt->MajorOperatingSystemVersion,
      pe_opt->MinorOperatingSystemVersion
    );
  }
  putchar('\n');

  printf(EXEDUMP_COLOR1"  Subsystem:          "EXEDUMP_COLOR2);
  uint16_t subsystem;
  if(is_pe_plus)
    subsystem = peplus_opt->Subsystem;
  else
    subsystem = pe_opt->Subsystem;
  switch(subsystem) {
    case IMAGE_SUBSYSTEM_NATIVE:
      puts("NT Native");
      break;
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:
      puts("Win32 GUI");
      break;
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:
      puts("Win32 Console");
      break;
    case IMAGE_SUBSYSTEM_OS2_CUI:
      puts("OS/2 Console");
      break;
    case IMAGE_SUBSYSTEM_POSIX_CUI:
      puts("POSIX Console");
      break;
    case IMAGE_SUBSYSTEM_NATIVE_WINDOWS:
      puts("Windows 9x VXD");
      break;
    case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:
      puts("Windows CE");
      break;
    case IMAGE_SUBSYSTEM_EFI_APPLICATION:
      puts("EFI Application");
      break;
    case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:
      puts("EFI Driver (w/ Boot services)");
      break;
    case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:
      puts("EFI Driver (w/ Runtime services)");
      break;
    case IMAGE_SUBSYSTEM_EFI_ROM:
      puts("EFI ROM");
      break;
    case IMAGE_SUBSYSTEM_XBOX:
      puts("XBOX");
      break;
    case IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION:
      puts("Windows boot application");
      break;
    default:
      puts("Unknown");
  }

  printf(EXEDUMP_COLOR1"  Subsystem Version:  "EXEDUMP_COLOR2);
  if(is_pe_plus) {
    printf("%d.%d",
      peplus_opt->MajorSubsystemVersion,
      peplus_opt->MinorSubsystemVersion
    );
  } else {
    printf("%d.%d",
      pe_opt->MajorSubsystemVersion,
      pe_opt->MinorSubsystemVersion
    );
  }
  putchar('\n');

  printf(EXEDUMP_COLOR1"  Checksum:           "EXEDUMP_COLOR2);
  if(is_pe_plus)
    printf("0x%08x", peplus_opt->CheckSum);
  else
    printf("0x%08x", pe_opt->CheckSum);
  putchar('\n');
}
