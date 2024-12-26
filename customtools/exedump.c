#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/prettyprint.h"
#include "../include/util.h"
#include "../config.h"

typedef struct elf_header_struct {
  unsigned int bitness;
  unsigned int endianness; // offset 5
  unsigned int os_abi; // offset 7
  unsigned int type; // offset 16/17
  unsigned int arch; // offset 18/19
} elf_header;

typedef struct pe_header_struct {
  unsigned int bitness;
  unsigned int arch;
  unsigned int image_type;
  char* subsystems[];
} pe_header;

void print_usage(char* argv0) {
  fprintf(stderr, "usage: %s [-c] [-f auto|elf|pe|ape] executable\n", argv0);
}

int main(int argc, char* argv[]) {
  char* exefmt = "auto"; // Default to autodetection
  char* c1 = ""; // Default to no colors
  char* c2 = ""; // Default to no colors

  int opt;
  // int cflag = 0;
  while((opt = getopt(argc, argv, ":f:c")) != -1) {
    switch(opt) {
      case 'f': // Specify executable format
        exefmt = optarg;
        break;
      case 'c': // Color output
        // cflag = 1;
        c1 = exedump_col1;
        c2 = exedump_col2;
        break;
      case '?':
        print_error("%s: invalid option -- '%c'", argv[0], optopt);
        print_usage(argv[0]);
        return 1;
        break;
    }
  }

  if(argc == optind) { // No file arg provided
    print_usage(argv[0]);
    return 1;
  }

  // LOAD FILE INTO MEM
  FILE* fileptr = fopen(argv[optind], "r");
  if(NULL == fileptr) {
    print_error("%s: could not open file \"%s\"", argv[0], argv[optind]);
    return 1;
  }
  
  //unsigned 
  char* buf = malloc(get_filesize(fileptr)+1);
  if(readfile(fileptr, buf) == -1) {
    print_error("%s: read error", argv[0]);
  }

  fclose(fileptr);
  // DONE LOADING FILE INTO MEM

  if(exefmt == "auto") { // Autodetect format
    if(buf[0] == 0x7f && buf[1] == 'E' && buf[2] == 'L' && buf[3] == 'F')
      exefmt == "elf";
  }

  if(exefmt == "auto") { // Autodetect failed
    print_error("%s: unable to identify executable type", argv[0]);
    return 1;
  }

  // TODO: put properties for each executable in a struct (something like struct elf, struct pe, struct ape)
  // TODO: implement actually portable executable support
  printf("| %sformat         %s| %s%s%s\n", c1, ANSI_NORM, c2, exefmt, ANSI_NORM);

  int i = 0; // we need this later
  if(!strcmp("elf", exefmt)) {
    // see https://wiki.osdev.org/ELF#ELF_Header for much easier to read details
    // see also https://www.sco.com/developers/gabi/latest/ch4.eheader.html
    // I also manually researched some parts myself (for dynamic loader detection)

    elf_header elf;

    printf("| %sendianness     %s| %s", c1, ANSI_NORM, c2);
    elf.endianness = !buf[5]; // defaults to 0 (little endian) by itself by the way
    if(elf.endianness == 0) {
      printf("little");
    } else if(elf.endianness == 1) {
      printf("big");
    } else {
      printf("unknown");
    }
    printf("%s\n", ANSI_NORM);

    // printf("| %sbitness        %s| %s%d bit%s\n", c1, ANSI_NORM, c2, buf[4]*32, ANSI_NORM);
    elf.bitness = (unsigned int)buf[4];
    printf("| %sbitness        %s| %s", c1, ANSI_NORM, c2);
    if(elf.bitness == 1 || elf.bitness == 2) {
      printf("%d bit", elf.bitness*32);
    } else if(elf.bitness == 3) {
      printf("128 bit"); // Cursed, but actually exists. see https://github.com/fpetrot/riscv-gnu-toolchain/blob/docker-128-bit/elf128-spec.md
    } else {
      printf("invalid bitness");
    }
    printf("%s\n", ANSI_NORM);

    printf("| %sarchitecture   %s| %s", c1, ANSI_NORM, c2);
    elf.arch = (unsigned int)buf[18+elf.endianness];
    switch(elf.arch) {
      case 0:
        printf("none");
        break;
      case 2:
        printf("sparc");
        break;
      case 3:  // fallthrough
      case 7:  // fallthrough
      case 62: // fallthrough
        printf("x86");
        break;
      case 4:
        printf("m68k");
        break;
      case 8:
        printf("mips");
        break;
      case 15:
        printf("hppa");
        break;
      case 20:
        printf("powerpc");
        break;
      case 40:  // fallthrough
      case 183:
        printf("arm");
        break;
      case 42:
        printf("superh");
        break;
      case 50:
        printf("ia64");
        break;
      case 75:
        printf("vax");
        break;
      case 83:
        printf("avr");
        break;
      case 243:
        printf("risc-v");
        break;
      default:
        printf("unknown");
    }
    printf("%s\n", ANSI_NORM);

    // Same as elf version normally ???
    //printf("| %shdr version     %s| %s%d%s\n", c1, ANSI_NORM, c2, buf[6], ANSI_NORM);

    // Sources: https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html and https://github.com/file/file/blob/master/magic/Magdir/elf
    printf("| %sos abi         %s| %s", c1, ANSI_NORM, c2);
    elf.os_abi = (unsigned int)buf[7];
    switch(elf.os_abi) {
      case 0:
        printf("system v");
        break;
      case 1:
        printf("hp-ux");
        break;
      case 2:
        printf("netbsd");
        break;
      case 3:
        printf("linux");
        break;
      case 4:
        printf("gnu hurd");
        break;
      case 5:
        printf("86open");
        break;
      case 6:
        printf("solaris");
        break;
      case 7:
        printf("aix");
        break;
      case 8:
        printf("irix");
        break;
      case 9:
        printf("freebsd");
        break;
      case 10:
        printf("tru64");
        break;
      case 11:
        printf("modesto");
        break;
      case 12:
        printf("openbsd");
        break;
      case 13:
        printf("openvms");
        break;
      case 14:
        printf("hp_nsk");
        break;
      case 15:
        printf("aros");
        break;
      case 16:
        printf("fenixos");
        break;
      case 17:
        printf("nuxi cloudabi");
        break;
      default:
        printf("unknown");
    }
    printf("%s\n", ANSI_NORM);

    printf("| %stype           %s| %s", c1, ANSI_NORM, c2);
    elf.type = (unsigned int)buf[16+elf.endianness];
    switch(elf.type) {
      case 0:
        printf("none");
      case 1:
        printf("relocatable");
        break;
      case 2:
        printf("static executable");
        break;
      case 3:
        printf("dynamically linked executable");
        break;
      case 4:
        printf("core dump");
        break;
      default:
        printf("unknown");
    }
    printf("%s\n", ANSI_NORM);

    // normally, we should check buf[20+(bitness*3)] (buf[20]/buf[23] depending on endianness), but ELF version is usually 1, so lets go the lazy route...
    printf("| %self version    %s| %s1%s\n", c1, ANSI_NORM, c2, ANSI_NORM);

    if(elf.type == 3) {
      printf("| %sdynamic loader %s| %s", c1, ANSI_NORM, c2);

      // TODO: find fool-proof way to get the dynamic elf loader for any elf executable (because there is no specific offset to it, it has to be found someway)
      size_t ldso_offset;
      switch(elf.arch) {
        case 0x3E: // tested on an x86_64 linux glibc executable
          ldso_offset = 504;
          break;
        case 0xB7: // tested on an arm64 linux musl executable
          ldso_offset = 568;
          break;
      }

      i = 0;
      unsigned char ch;
      while(ch != '\0') {
        ch = buf[ldso_offset+i];
        printf("%c", ch);
        i++;
      }
      printf("%s\n", ANSI_NORM);
    }

  } else if(!strcmp("pe", exefmt)) {
    // TODO: get PE metadata and other properties (bitness, ...)
    // See https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
    // I also manually researched some parts myself
    // TODO: use pe_header struct here

    // pe_header pe;

    printf("| %sarchitecture   %s| %s", c1, ANSI_NORM, c2);

    int coff_offset_begin = 132; // Default x86
    if(buf[2] == 'x') { // ARM
      coff_offset_begin = 124;
    }

    switch(buf[coff_offset_begin]) {
      case 0x00:
        printf("any/unknown");
        break;
      case 0x4c:
        if(buf[coff_offset_begin+1] == 0x01) {
          printf("x86");
        } else {
          printf("unknown");
        }
        break;
      case 0x64:
        if(buf[coff_offset_begin+1] == 0x86) {
          printf("x86_64");
        } else if(buf[coff_offset_begin+1] == 0xaa) {
          printf("arm64");
        } else {
          printf("unknown");
        }
        break;
      case 0xc4:
        printf("arm32");
        if(buf[coff_offset_begin+1] == 0x01) {
          printf(" thumb");
        }
        break;
      default:
        printf("unknown");
    }
    printf("%s\n", ANSI_NORM);
    
    printf("| %spe image type  %s| %s", c1, ANSI_NORM, c2);
    int pe_type = 2; // Default to 2; 0 = PE32, 1 = PE32+, >=2 unknown variant
    // TODO: detect PE type (PE32, PE32+)
    for(i = 0; i < strlen(buf); i++) {
      if(buf[i] == 0xb0) {
        if(buf[i+1] == 0x01) {
          pe_type = 0;
          break;
        } else if(buf[i+1] == 0x02) {
          pe_type = 1;
          break;
        }
      }
    }
    printf("pe32");
    if(pe_type == 1)
      printf("+");
    if(pe_type > 1)
      printf(" unknown variant");

    i = 0;
    for(i = 0; i < strlen(buf); i++) {
      if(buf[i] == 'P' && buf[i+1] == 'E' && (buf[i+2] == buf[i+3] == '\0'))
        break;
    }
    int pe_hdr_offset = i;
    printf("%s\n", ANSI_NORM);

    printf("| %ssubsystems     %s| %s", c1, ANSI_NORM, c2);
    // TODO: detect subsystems (win32 console, win32 gui, native, efi, dll console, dll gui, ...)
    printf("%s\n", ANSI_NORM);

  }

  // TODO: get program entry,header table offsets ...
  // TODO: get list of linked libraries (if any) (dynamic executables only)

  // free buffer when done
  free(buf);
  return 0;
}
