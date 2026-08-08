#ifndef PE_H
#define PE_H

#include <stdint.h>

typedef struct {
  uint16_t Magic; // 0x5a4d
  uint8_t reserved[58]; // we don't really need the rest...
  uint32_t e_lfanew;
} DosStub_t;

typedef struct {
  uint32_t Magic; // 0x00004550
  uint16_t Machine;
  uint16_t NumberOfSections;
  uint32_t TimeDateStamp;
  uint32_t NumberOfSymbols;
  uint32_t PointerToSymbolTable;
  uint16_t SizeOfOptionalHeader;
  uint16_t Characteristics;
} PeHeader_t;

typedef struct {
	uint16_t Magic; // 0x010b
	uint8_t  MajorLinkerVersion;
	uint8_t  MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint32_t BaseOfData;
	uint32_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint32_t SizeOfStackReserve;
	uint32_t SizeOfStackCommit;
	uint32_t SizeOfHeapReserve;
	uint32_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;
} Pe32OptHeader_t;

typedef struct {
	uint16_t Magic; // 0x020b
	uint8_t  MajorLinkerVersion;
	uint8_t  MinorLinkerVersion;
	uint32_t SizeOfCode;
	uint32_t SizeOfInitializedData;
	uint32_t SizeOfUninitializedData;
	uint32_t AddressOfEntryPoint;
	uint32_t BaseOfCode;
	uint64_t ImageBase;
	uint32_t SectionAlignment;
	uint32_t FileAlignment;
	uint16_t MajorOperatingSystemVersion;
	uint16_t MinorOperatingSystemVersion;
	uint16_t MajorImageVersion;
	uint16_t MinorImageVersion;
	uint16_t MajorSubsystemVersion;
	uint16_t MinorSubsystemVersion;
	uint32_t Win32VersionValue;
	uint32_t SizeOfImage;
	uint32_t SizeOfHeaders;
	uint32_t CheckSum;
	uint16_t Subsystem;
	uint16_t DllCharacteristics;
	uint64_t SizeOfStackReserve;
	uint64_t SizeOfStackCommit;
	uint64_t SizeOfHeapReserve;
	uint64_t SizeOfHeapCommit;
	uint32_t LoaderFlags;
	uint32_t NumberOfRvaAndSizes;
} Pe32PlusOptHeader_t;

#define PE_MAG1 'P'
#define PE_MAG2 'E'
#define PE_MAG3 '\0'
#define PE_MAG4 '\0'

/* Machine Types */

#define IMAGE_FILE_MACHINE_UNKNOWN 0x0 // The contents of this field are assumed to be applicable to any machine type
#define IMAGE_FILE_MACHINE_ALPHA 0x184 //Alpha AXP, 32-bit address space
#define IMAGE_FILE_MACHINE_ALPHA64 0x284 //Alpha 64, 64-bit address space
#define IMAGE_FILE_MACHINE_AM33 0x1d3 //Matsushita AM33
#define IMAGE_FILE_MACHINE_AMD64 0x8664 // x64
#define IMAGE_FILE_MACHINE_ARM 0x1c0 // ARM little endian
#define IMAGE_FILE_MACHINE_ARM64 0xaa64 // ARM 64
#define IMAGE_FILE_MACHINE_ARM64EC 0xA641 //ABI that enables interoperability between native ARM64 and emulated x64 code.
#define IMAGE_FILE_MACHINE_ARM64X 0xA64E //Binary format that allows both native ARM64 and ARM64EC code to coexist in the same file.
#define IMAGE_FILE_MACHINE_ARMNT 0x1c4 // ARM Thumb-2 little endian
#define IMAGE_FILE_MACHINE_EBC 0xebc // EFI byte code
#define IMAGE_FILE_MACHINE_I386 0x14c // Intel 386 or later processors and compatible processors
#define IMAGE_FILE_MACHINE_IA64 0x200 // Intel Itanium processor family
#define IMAGE_FILE_MACHINE_M32R 0x9041 // Mitsubishi M32R little endian
#define IMAGE_FILE_MACHINE_MIPS16 0x266 // MIPS16
#define IMAGE_FILE_MACHINE_MIPSFPU 0x366 // MIPS with FPU
#define IMAGE_FILE_MACHINE_MIPSFPU16 0x466 // MIPS16 with FPU
#define IMAGE_FILE_MACHINE_POWERPC 0x1f0 // Power PC little endian
#define IMAGE_FILE_MACHINE_POWERPCFP 0x1f1 // Power PC with floating point support
#define IMAGE_FILE_MACHINE_R4000 0x166 // MIPS little endian
#define IMAGE_FILE_MACHINE_RISCV32 0x5032 // RISC-V 32-bit address space
#define IMAGE_FILE_MACHINE_RISCV64 0x5064 // RISC-V 64-bit address space
#define IMAGE_FILE_MACHINE_RISCV128 0x5128 // RISC-V 128-bit address space
#define IMAGE_FILE_MACHINE_SH3 0x1a2 // Hitachi SH3
#define IMAGE_FILE_MACHINE_SH3DSP 0x1a3 // Hitachi SH3 DSP
#define IMAGE_FILE_MACHINE_SH4 0x1a6 // Hitachi SH4
#define IMAGE_FILE_MACHINE_SH5 0x1a8 // Hitachi SH5
#define IMAGE_FILE_MACHINE_THUMB 0x1c2 // Thumb
#define IMAGE_FILE_MACHINE_WCEMIPSV2 0x169 // MIPS little-endian WCE v2

/* Characteristics */

#define IMAGE_FILE_RELOCS_STRIPPED 0x0001 // Image only, Windows CE, and Microsoft Windows NT® and later. This indicates that the file does not contain base relocations and must therefore be loaded at its preferred base address. If the base address is not available, the loader reports an error. The default behavior of the linker is to strip base relocations from executable (EXE) files.
#define IMAGE_FILE_EXECUTABLE_IMAGE 0x0002 // Image only. This indicates that the image file is valid and can be run. If this flag is not set, it indicates a linker error.
#define IMAGE_FILE_LINE_NUMS_STRIPPED 0x0004 // COFF line numbers have been removed. This flag is deprecated and should be zero.
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED 0x0008 // COFF symbol table entries for local symbols have been removed. This flag is deprecated and should be zero.
#define IMAGE_FILE_AGGRESSIVE_WS_TRIM 0x0010 // Obsolete. Aggressively trim working set. This flag is deprecated for Windows 2000 and later and must be zero.
#define IMAGE_FILE_LARGE_ADDRESS_AWARE 0x0020 // Application can handle > 2‑GB addresses.
#define IMAGE_FILE_BYTES_REVERSED_LO 0x0080 // Little endian: the least significant bit (LSB) precedes the most significant bit (MSB) in memory. This flag is deprecated and should be zero.
#define IMAGE_FILE_32BIT_MACHINE 0x0100 // Machine is based on a 32-bit-word architecture.
#define IMAGE_FILE_DEBUG_STRIPPED 0x0200 // Debugging information is removed from the image file.
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP 0x0400 // If the image is on removable media, fully load it and copy it to the swap file.
#define IMAGE_FILE_NET_RUN_FROM_SWAP 0x0800 // If the image is on network media, fully load it and copy it to the swap file.
#define IMAGE_FILE_SYSTEM 0x1000 // The image file is a system file, not a user program.
#define IMAGE_FILE_DLL 0x2000 // The image file is a dynamic-link library (DLL). Such files are considered executable files for almost all purposes, although they cannot be directly run.
#define IMAGE_FILE_UP_SYSTEM_ONLY 0x4000 // The file should be run only on a uniprocessor machine.
#define IMAGE_FILE_BYTES_REVERSED_HI 0x8000 // Big endian: the MSB precedes the LSB in memory. This flag is deprecated and should be zero.

/* Subsystems */

#define IMAGE_SUBSYSTEM_UNKNOWN 0 // An unknown subsystem
#define IMAGE_SUBSYSTEM_NATIVE 1 // Device drivers and native Windows processes
#define IMAGE_SUBSYSTEM_WINDOWS_GUI 2 // The Windows graphical user interface (GUI) subsystem
#define IMAGE_SUBSYSTEM_WINDOWS_CUI 3 // The Windows character subsystem
#define IMAGE_SUBSYSTEM_OS2_CUI 5 // The OS/2 character subsystem
#define IMAGE_SUBSYSTEM_POSIX_CUI 7 // The Posix character subsystem
#define IMAGE_SUBSYSTEM_NATIVE_WINDOWS 8 // Native Win9x driver
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI 9 // Windows CE
#define IMAGE_SUBSYSTEM_EFI_APPLICATION 10 // An Extensible Firmware Interface (EFI) application
#define IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11 // An EFI driver with boot services
#define IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 12 // An EFI driver with run-time services
#define IMAGE_SUBSYSTEM_EFI_ROM 13 // An EFI ROM image
#define IMAGE_SUBSYSTEM_XBOX 14 // XBOX
#define IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION 16 // Windows boot application.

#endif // PE_H
