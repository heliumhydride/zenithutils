#ifndef ELF_H
#define ELF_H

#include <stdint.h>

typedef struct {
  uint8_t  e_ident[16];
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint32_t e_entry;
  uint32_t e_phoff;
  uint32_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
} Elf32_Ehdr;

typedef struct {
  uint32_t p_type;
  uint32_t p_offset;
  uint32_t p_vaddr;
  uint32_t p_paddr;
  uint32_t p_filesz;
  uint32_t p_memsz;
  uint32_t p_flags;
  uint32_t p_align;
} Elf32_Phdr;

typedef struct {
    uint8_t  e_ident[16];   /* Magic number and other info */
    uint16_t e_type;        /* Object file type */
    uint16_t e_machine;     /* Architecture */
    uint32_t e_version;     /* Object file version */
    uint64_t e_entry;       /* Entry point virtual address */
    uint64_t e_phoff;       /* Program header table file offset */
    uint64_t e_shoff;       /* Section header table file offset */
    uint32_t e_flags;       /* Processor-specific flags */
    uint16_t e_ehsize;      /* ELF header size in bytes */
    uint16_t e_phentsize;   /* Program header table entry size */
    uint16_t e_phnum;       /* Program header table entry count */
    uint16_t e_shentsize;   /* Section header table entry size */
    uint16_t e_shnum;       /* Section header table entry count */
    uint16_t e_shstrndx;    /* Section header string table index */
} Elf64_Ehdr;

typedef struct {
    uint32_t p_type;        /* Segment type */
    uint32_t p_flags;       /* Segment flags */
    uint64_t p_offset;      /* Segment file offset */
    uint64_t p_vaddr;       /* Segment virtual address */
    uint64_t p_paddr;       /* Segment physical address */
    uint64_t p_filesz;      /* Segment size in file */
    uint64_t p_memsz;       /* Segment size in memory */
    uint64_t p_align;       /* Segment alignment */
} Elf64_Phdr;

#define ELF_MAGIC "\177ELF"
#define ELF_MAG1  '\177'
#define ELF_MAG2  'E'
#define ELF_MAG3  'L'
#define ELF_MAG4  'F'

#define ELF_BITS_32  1
#define ELF_BITS_64  2

#define ELF_LSB      1
#define ELF_MSB      2

#define ABI_SYSV     0
#define ABI_HPUX     1
#define ABI_NETBSD   2
#define ABI_LINUX    3
#define ABI_HURD     4
#define ABI_86OPEN   5
#define ABI_SOLARIS  6
#define ABI_AIX      7
#define ABI_IRIS     8
#define ABI_FREEBSD  9
#define ABI_TRU64   10
#define ABI_MODESTO 11
#define ABI_OPENBSD 12
#define ABI_ARM_AEABI  64
#define ABI_ARM        97
#define ABI_STANDALONE 255


#define EM_NONE      0
#define EM_SPARC     2
#define EM_386       3
#define EM_68K       4
#define EM_MIPS      8
#define EM_MIPS_RS3_LE 10
#define EM_PPC      20
#define EM_PPC64    21
#define EM_S390     22
#define EM_ARM      40
#define EM_SH       42
#define EM_SPARCV9  43
#define EM_IA_64    50
#define EM_X86_64   62
#define EM_AVR      83
#define EM_AARCH64 183
#define EM_CUDA    190
#define EM_AMDGPU  224
#define EM_RISCV   243
#define EM_LOONG   258

#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4

#endif // ELF_H
