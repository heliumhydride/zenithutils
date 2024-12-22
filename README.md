# zenithutils
An nth implementation of coreutils / util-linux / chimerautils / busybox / sbase / ubase / plan9base / ...

### implements:
  - coreutils (ls, cp, uname, ln, chmod, mv, rm, ...)
  - util-linux (fdisk, lsblk, lscpu, losetup, mount, ...)
  - procps-ng programs and psutils programs (groupped as procutils in Makefile)
  - sharutils (shar, uuencode, uudecode)
  - find
  - iconv
  - diff
  - grep
  - sed
  - patch
  - su
  - which
  - gzip
  - possible future implementations of awk and bc
  - read, time from sh
  - strings
  - ed (integrated in coreutils in Makefile)
  - dos2unix/unix2dos (integrated in coreutils in Makefile)
  - portions of shadow (passwdutils in Makefile)

### required dependencies:
  - a c99 toolchain such as gcc / mingw / Clang+LLVM / tcc... but not visual c
  - GNU make
  - mkdir+cp commands from coreutils/busybox (yes quite ironic i know...)
  - [libsodium](https://github.com/jedisct1/libsodium) for 'uuidgen', 'rng' and 'mktemp'
  - [openpam](https://git.des.dev/openpam/openpam/wiki) / linux-pam for 'su'
  - [zlib](https://zlib.net) / [zlib-ng](https://github.com/zlib-ng/zlib-ng) with zlib compat for 'gzip'
  - [netbsd-curses](https://github.com/sabotage-linux/netbsd-curses) / [ncurses](https://invisible-island.net/ncurses/) for Linux/*BSD OR [pdcurses](https://github.com/wmcbrine/PDCurses) for Windows
  - [libicu](https://icu.unicode.org/) for iconv

### recommended to go along with zenithutils:
  - for a more feature-packed environment:
    - [onetrueawk](https://github.com/onetrueawk/awk) (build fails for Windows)
    - [bc-gh](https://github.com/gavinhoward/bc) (build fails for Windows)
    - [nq](https://github.com/leahneukirchen/nq) (useful when building large software) (not supported on Windows)
    - [libarchive](https://libarchive.de) // [paxmirabilis](http://www.mirbsd.org/pax.htm) (aka. mircpio) (not supported on Windows)
    - [mksh](http://www.mirbsd.org/mksh.html) (not supported on Windows) // [mksh/win32](http://www.mirbsd.org/permalinks/wlog-10_e20130718-tg.htm)
    - [yash](https://magicant.github.io/yash/) (not supported on Windows)

  - for bootable linux systems:
    - [nyagetty](https://github.com/chimera-linux/nyagetty) (not supported on Windows)

### why ? the alternatives work pretty well.
  - Because I wanted a replacement for chimerautils + util-linux on my custom distro im making
  - I also wanted a userland that could compile for both Linux and Windows NT without needing Cygwin (akin to busybox-w32) but more complete and more BSD-like
  - I learn stuff and I'm bored

### compatibility goals (in order of priority):
  - Linux with musl, glibc, uclibc-ng, bionic libc (Android) and llvm libc
  - Windows 2000+ (x86_64, x86, arm64, arm)
  - *BSD
  - MacOS (x86_64, arm64)
  - Cosmopolitan libc

