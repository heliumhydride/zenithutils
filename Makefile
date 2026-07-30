include config.mk

all: coreutils customtools diffutils findutils grep gzip iconv patch procutils sed sharutils su util-linux which passwdutils

# yes read, like the shellscript read (with -r, and all that good stuff)
customtools: o/bin/zenithutils_version o/bin/ascii o/bin/rng o/bin/read o/bin/strings o/bin/exedump o/bin/usleep o/bin/clear o/bin/time

# logname is a link to whoami
# md5sum is a link to md5
# [ is a link to test
# how would 'nohup' work on Windows?
coreutils: o/bin/cat o/bin/nproc o/bin/ls o/bin/uname o/bin/seq o/bin/pwd o/bin/true o/bin/false o/bin/yes o/bin/dirname o/bin/basename o/bin/tac o/bin/sleep o/bin/wc o/bin/mktemp o/bin/tty  o/bin/base64 o/bin/base32 o/bin/mkdir o/bin/rmdir o/bin/test o/sbin/mknod o/bin/whoami o/bin/readlink o/bin/mkfifo o/bin/cp o/bin/mv o/bin/rm o/bin/sync o/bin/tee o/bin/tail o/bin/head o/bin/sort o/bin/shred o/bin/touch o/bin/timeout o/bin/truncate o/bin/uniq o/bin/users o/bin/nice o/bin/ln o/bin/install o/bin/id o/bin/hostname o/bin/groups o/bin/df o/sbin/chroot o/bin/chmod o/bin/chown o/bin/cut o/bin/date o/bin/dd o/bin/fmt o/bin/fold o/bin/md5 o/bin/sha1sum o/bin/sha224sum o/bin/sha256sum o/bin/sha384sum o/bin/sha512sum o/bin/pr o/bin/tr o/bin/chgrp o/bin/echo o/bin/comm o/bin/du o/bin/env o/bin/expand o/bin/expr o/bin/join o/bin/od o/bin/printf o/bin/split o/bin/stty o/bin/tsort o/bin/unexpand o/bin/who o/bin/nl o/bin/dos2unix o/bin/unix2dos o/bin/ed o/bin/printenv o/bin/factor o/bin/nohup o/bin/numfmt o/bin/paste o/bin/pathchk o/bin/finger o/bin/realpath o/bin/stat o/bin/shuf

# do we really need 'rename' and 'hardlink' ? (see 'mv' and 'ln')
# agetty not implemented, see nyagetty from chimera linux
# hwclock not being implemented for now
# losetup, pivot_root, ionice, write, show a "does not apply to windows" and return 1
# for mkswap/swapon/swapoff on windows: do we have functions in the win32 api to change pagefile settings ?
# for login on windows: use as a frontend to LogonUI/runas.exe maybe ? kind of a strech but I don't see what else login.exe would do...
# fsck on windows: do we just 'execvp("chkdsk.exe", ...);' ?
util-linux: o/bin/rev o/sbin/nologin o/bin/uuidgen o/bin/kill o/bin/lscpu o/bin/column o/bin/blkid o/bin/cal o/bin/cfdisk o/bin/chsh o/bin/col o/bin/dmesg o/bin/eject o/bin/fallocate o/sbin/fdisk o/bin/findfs o/sbin/fsck o/bin/getopt o/bin/hexdump o/bin/ionice o/bin/last o/bin/login o/sbin/losetup o/bin/lsblk o/bin/lslogins o/bin/mcookie o/sbin/mkfs o/sbin/mkswap o/bin/more o/sbin/mount o/bin/mountpoint o/sbin/pivot_root o/bin/renice o/bin/write o/bin/whereis o/bin/swapon o/bin/swapoff

findutils: o/bin/xargs o/bin/find 

diffutils: o/bin/diff o/bin/cmp o/bin/sdiff

su: o/bin/su

which: o/bin/which

# egrep and fgrep are links to grep
grep: o/bin/grep

sed: o/bin/sed

patch: o/bin/patch

# gunzip and zcat are links to gzip
gzip: o/bin/gzip

# sysctl will either show a "does not apply to windows" or will implement some kind of command line windows control panel
# uptime is a link to w
procutils: o/bin/w o/bin/top o/bin/pstree o/bin/fuser o/bin/killall o/bin/ps o/bin/pkill o/sbin/sysctl o/bin/pidof o/bin/free o/bin/pgrep o/bin/vmstat

sharutils: o/bin/shar o/bin/uuencode o/bin/uudecode

iconv: o/bin/iconv

passwdutils: o/bin/passwd o/sbin/chage o/sbin/useradd o/sbin/userdel o/sbin/usermod o/sbin/groupadd o/sbin/groupdel o/sbin/groupmod o/sbin/sg

o/bin/zenithutils_version: init_outdir customtools/zenithutils_version.c
	$(CC) $(CFLAGS) -o o/bin/zenithutils_version customtools/zenithutils_version.c

lib/prettyprint.o: lib/prettyprint.c
	$(CC) $(CFLAGS) -c -o lib/prettyprint.o lib/prettyprint.c

coreutils/cat.o: coreutils/cat.c
	$(CC) $(CFLAGS) -c -o coreutils/cat.o coreutils/cat.c

o/bin/cat: init_outdir lib/prettyprint.o coreutils/cat.o
	$(LD) $(LDFLAGS) -o o/bin/cat lib/prettyprint.o coreutils/cat.o

o/bin/nproc: init_outdir coreutils/nproc.c
	$(CC) $(CFLAGS) -o o/bin/nproc coreutils/nproc.c

coreutils/ls.o: coreutils/ls.c
	$(CC) $(CFLAGS) -c -o coreutils/ls.o coreutils/ls.c

o/bin/ls: init_outdir lib/prettyprint.o lib/util.o coreutils/ls.o
	$(LD) $(LDFLAGS) -o o/bin/ls lib/prettyprint.o lib/util.o coreutils/ls.o

lib/utsname_winnt.o: lib/utsname_winnt.c
	$(CC) $(CFLAGS) -c -o lib/utsname_winnt.o lib/utsname_winnt.c

coreutils/uname.o: coreutils/uname.c
	$(CC) $(CFLAGS) -c -o coreutils/uname.o coreutils/uname.c

o/bin/uname: init_outdir lib/prettyprint.o lib/utsname_winnt.o coreutils/uname.o
	$(LD) $(LDFLAGS) -o o/bin/uname lib/prettyprint.o lib/utsname_winnt.o coreutils/uname.o 

lib/util.o: lib/util.c
	$(CC) $(CFLAGS) -c -o lib/util.o lib/util.c

lib/util_m.o: lib/util_m.c
	$(CC) $(CFLAGS) -c -o lib/util_m.o lib/util_m.c

which/which.o: which/which.c
	$(CC) $(CFLAGS) -c -o which/which.o which/which.c

o/bin/which: init_outdir lib/prettyprint.o lib/util.o which/which.o
	$(LD) $(LDFLAGS) -o o/bin/which lib/prettyprint.o lib/util.o which/which.o 

coreutils/seq.o: coreutils/seq.c
	$(CC) $(CFLAGS) -c -o coreutils/seq.o coreutils/seq.c

o/bin/seq: init_outdir lib/prettyprint.o lib/util.o coreutils/seq.o
	$(LD) $(LDFLAGS) -o o/bin/seq lib/prettyprint.o lib/util.o coreutils/seq.o 

o/bin/pwd: init_outdir lib/prettyprint.o lib/util.o coreutils/pwd.o
	$(LD) $(LDFLAGS) -o o/bin/pwd lib/prettyprint.o lib/util.o coreutils/pwd.o 

o/bin/true: init_outdir coreutils/true.c
	$(CC) $(CFLAGS) -o o/bin/true coreutils/true.c

o/bin/false: init_outdir coreutils/false.c
	$(CC) $(CFLAGS) -o o/bin/false coreutils/false.c

o/bin/yes: init_outdir coreutils/yes.c
	$(CC) $(CFLAGS) -o o/bin/yes coreutils/yes.c

o/bin/dirname: init_outdir coreutils/dirname.c
	$(CC) $(CFLAGS) -o o/bin/dirname coreutils/dirname.c

o/bin/basename: init_outdir coreutils/basename.c
	$(CC) $(CFLAGS) -o o/bin/basename coreutils/basename.c

coreutils/tac.o: coreutils/tac.c
	$(CC) $(CFLAGS) -c -o coreutils/tac.o coreutils/tac.c

o/bin/tac: init_outdir lib/prettyprint.o lib/util.o coreutils/tac.o
	$(LD) $(LDFLAGS) -o o/bin/tac lib/prettyprint.o lib/util.o coreutils/tac.o

o/bin/sleep: init_outdir coreutils/sleep.c
	$(CC) $(CFLAGS) -o o/bin/sleep coreutils/sleep.c

coreutils/wc.o: coreutils/wc.c
	$(CC) $(CFLAGS) -c -o coreutils/wc.o coreutils/wc.c

o/bin/wc: init_outdir lib/prettyprint.o coreutils/wc.o
	$(LD) $(LDFLAGS) -o o/bin/wc lib/prettyprint.o coreutils/wc.o

coreutils/tr.o: coreutils/tr.c
	$(CC) $(CFLAGS) -c -o coreutils/tr.o coreutils/tr.c

o/bin/tr: init_outdir lib/prettyprint.o lib/util.o coreutils/tr.o
	$(LD) $(LDFLAGS) -o o/bin/tr lib/prettyprint.o lib/util.o coreutils/tr.o

coreutils/base64.o: coreutils/base64.c config.h
	$(CC) $(CFLAGS) -c -o coreutils/base64.o coreutils/base64.c

o/bin/base64: init_outdir lib/prettyprint.o lib/util.o lib/base64.o coreutils/base64.o
	$(LD) $(LDFLAGS) -o o/bin/base64 lib/prettyprint.o lib/util.o lib/base64.o coreutils/base64.o 

coreutils/base32.o: coreutils/base32.c config.h
	$(CC) $(CFLAGS) -c -o coreutils/base32.o coreutils/base32.c

o/bin/base32: init_outdir lib/prettyprint.o lib/util.o coreutils/base32.o
	$(LD) $(LDFLAGS) -o o/bin/base32 lib/prettyprint.o lib/util.o coreutils/base32.o 

o/bin/shar: init_outdir sharutils/shar.sh
	cp sharutils/shar.sh o/bin/shar

sharutils/uuencode.o: sharutils/uuencode.c lib/base64.o
	$(CC) $(CFLAGS) -c -o sharutils/uuencode.o lib/base64.o sharutils/uuencode.c

o/bin/uuencode: init_outdir lib/prettyprint.o lib/base64.o sharutils/uuencode.o
	$(LD) $(LDFLAGS) -o o/bin/uuencode lib/prettyprint.o lib/base64.o sharutils/uuencode.o 

sharutils/uudecode.o: sharutils/uudecode.c
	$(CC) $(CFLAGS) -c -o sharutils/uudecode.o sharutils/uudecode.c

o/bin/uudecode: init_outdir lib/prettyprint.o lib/util.o sharutils/uudecode.o
	$(LD) $(LDFLAGS) -o o/bin/uudecode lib/prettyprint.o lib/util.o sharutils/uudecode.o 

coreutils/mktemp.o: coreutils/mktemp.c
	$(CC) $(CFLAGS) -c -o coreutils/mktemp.o coreutils/mktemp.c

# requires libsodium
o/bin/mktemp: init_outdir lib/prettyprint.o lib/util.o coreutils/mktemp.o
	$(LD) $(LDFLAGS) -o o/bin/mktemp lib/prettyprint.o lib/util.o coreutils/mktemp.o -lsodium

coreutils/mknod.o: coreutils/mknod.c
	$(CC) $(CFLAGS) -c -o coreutils/mknod.o coreutils/mknod.c

o/sbin/mknod: init_outdir lib/prettyprint.o lib/util.o coreutils/mknod.o
	$(LD) $(LDFLAGS) -o o/sbin/mknod lib/prettyprint.o lib/util.o coreutils/mknod.o 

coreutils/mkfifo.o: coreutils/mkfifo.c
	$(CC) $(CFLAGS) -c -o coreutils/mkfifo.o coreutils/mkfifo.c

o/bin/mkfifo: init_outdir lib/prettyprint.o coreutils/mkfifo.o
	$(LD) $(LDFLAGS) -o o/bin/mkfifo lib/prettyprint.o coreutils/mkfifo.o

customtools/read.o: customtools/read.c
	$(CC) $(CFLAGS) -c -o customtools/read.o customtools/read.c

o/bin/read: init_outdir lib/prettyprint.o customtools/read.o
	$(LD) $(LDFLAGS) -o o/bin/read lib/prettyprint.o customtools/read.o

customtools/strings.o: customtools/strings.c
	$(CC) $(CFLAGS) -c -o customtools/strings.o customtools/strings.c

o/bin/strings: init_outdir lib/prettyprint.o lib/util.o customtools/strings.o
	$(LD) $(LDFLAGS) -o o/bin/strings lib/prettyprint.o lib/util.o customtools/strings.o

o/bin/ascii: init_outdir customtools/ascii.c
	$(CC) $(CFLAGS) -o o/bin/ascii customtools/ascii.c

util-linux/rev.o: util-linux/rev.c
	$(CC) $(CFLAGS) -c -o util-linux/rev.o util-linux/rev.c

o/bin/rev: init_outdir lib/prettyprint.o lib/util.o util-linux/rev.o
	$(LD) $(LDFLAGS) -o o/bin/rev lib/prettyprint.o lib/util.o util-linux/rev.o

o/sbin/nologin: init_outdir util-linux/nologin.c
	$(CC) $(CFLAGS) -o o/sbin/nologin util-linux/nologin.c

util-linux/uuidgen.o: util-linux/uuidgen.c
	$(CC) $(CFLAGS) -c -o util-linux/uuidgen.o util-linux/uuidgen.c

# requires libsodium
o/bin/uuidgen: init_outdir lib/prettyprint.o lib/util.o util-linux/uuidgen.o
	$(LD) $(LDFLAGS) -o o/bin/uuidgen lib/prettyprint.o lib/util.o util-linux/uuidgen.o -lsodium

findutils/xargs.o: findutils/xargs.c
	$(CC) $(CFLAGS) -c -o findutils/xargs.o findutils/xargs.c

o/bin/xargs: init_outdir lib/prettyprint.o findutils/xargs.o
	$(LD) $(LDFLAGS) -o o/bin/xargs lib/prettyprint.o findutils/xargs.o

customtools/rng.o: customtools/rng.c
	$(CC) $(CFLAGS) -c -o customtools/rng.o customtools/rng.c

# requires libsodium
o/bin/rng: init_outdir lib/prettyprint.o lib/util.o customtools/rng.o
	$(LD) $(LDFLAGS) -o o/bin/rng lib/prettyprint.o lib/util.o customtools/rng.o -lsodium

customtools/exedump.o: customtools/exedump.c config.h
	$(CC) $(CFLAGS) -c -o customtools/exedump.o customtools/exedump.c

o/bin/exedump: init_outdir lib/prettyprint.o lib/util.o customtools/exedump.o
	$(LD) $(LDFLAGS) -o o/bin/exedump lib/prettyprint.o lib/util.o customtools/exedump.o -lm

customtools/usleep.o: customtools/usleep.c
	$(CC) $(CFLAGS) -c -o customtools/usleep.o customtools/usleep.c

o/bin/usleep: init_outdir lib/prettyprint.o lib/util.o customtools/usleep.o
	$(LD) $(LDFLAGS) -o o/bin/usleep lib/prettyprint.o lib/util.o customtools/usleep.o

procutils/w.o: procutils/w.c
	$(CC) $(CFLAGS) -c -o procutils/w.o procutils/w.c

o/bin/w: init_outdir lib/prettyprint.o lib/util.o lib/util_m.o procutils/w.o
	$(LD) $(LDFLAGS) -o o/bin/w -lm lib/prettyprint.o lib/util.o lib/util_m.o procutils/w.o

coreutils/whoami.o: coreutils/whoami.c
	$(CC) $(CFLAGS) -c -o coreutils/whoami.o coreutils/whoami.c

o/bin/whoami: init_outdir lib/prettyprint.o coreutils/whoami.o
	$(LD) $(LDFLAGS) -o o/bin/whoami lib/prettyprint.o coreutils/whoami.o

coreutils/tty.o: coreutils/tty.c
	$(CC) $(CFLAGS) -c -o coreutils/tty.o coreutils/tty.c

o/bin/tty: init_outdir coreutils/tty.o
	$(LD) $(LDFLAGS) -o o/bin/tty coreutils/tty.o

coreutils/test.o: coreutils/test.c
	$(CC) $(CFLAGS) -c -o coreutils/test.o coreutils/test.c

o/bin/test: init_outdir lib/prettyprint.o coreutils/test.o
	$(LD) $(LDFLAGS) -o o/bin/test lib/prettyprint.o coreutils/test.o

coreutils/uniq.o: coreutils/uniq.c
	$(CC) $(CFLAGS) -c -o coreutils/uniq.o coreutils/uniq.c

o/bin/uniq: init_outdir lib/prettyprint.o lib/util.o coreutils/uniq.o
	$(LD) $(LDFLAGS) -o o/bin/uniq lib/prettyprint.o lib/util.o coreutils/uniq.o

coreutils/mkdir.o: coreutils/mkdir.c
	$(CC) $(CFLAGS) -c -o coreutils/mkdir.o coreutils/mkdir.c

o/bin/mkdir: init_outdir lib/prettyprint.o lib/util.o coreutils/mkdir.o
	$(LD) $(LDFLAGS) -o o/bin/mkdir lib/prettyprint.o lib/util.o coreutils/mkdir.o

coreutils/rmdir.o: coreutils/rmdir.c
	$(CC) $(CFLAGS) -c -o coreutils/rmdir.o coreutils/rmdir.c

o/bin/rmdir: init_outdir lib/prettyprint.o coreutils/rmdir.o
	$(LD) $(LDFLAGS) -o o/bin/rmdir lib/prettyprint.o coreutils/rmdir.o

coreutils/head.o: coreutils/head.c
	$(CC) $(CFLAGS) -c -o coreutils/head.o coreutils/head.c

o/bin/head: init_outdir lib/prettyprint.o lib/util.o coreutils/head.o
	$(LD) $(LDFLAGS) -o o/bin/head lib/prettyprint.o lib/util.o coreutils/head.o

coreutils/tail.o: coreutils/tail.c
	$(CC) $(CFLAGS) -c -o coreutils/tail.o coreutils/tail.c

o/bin/tail: init_outdir lib/prettyprint.o lib/util.o coreutils/tail.o
	$(LD) $(LDFLAGS) -o o/bin/tail lib/prettyprint.o lib/util.o coreutils/tail.o

customtools/clear.o: customtools/clear.c
	$(CC) $(CFLAGS) -c -o customtools/clear.o customtools/clear.c

o/bin/clear: init_outdir customtools/clear.o
	$(LD) $(LDFLAGS) -o o/bin/clear customtools/clear.o

coreutils/readlink.o: coreutils/readlink.c
	$(CC) $(CFLAGS) -c -o coreutils/readlink.o coreutils/readlink.c

o/bin/readlink: init_outdir lib/prettyprint.o coreutils/readlink.o
	$(LD) $(LDFLAGS) -o o/bin/readlink lib/prettyprint.o coreutils/readlink.o

clean:
	rm -rf o/* coreutils/*.o customtools/*.o diffutils/*.o findutils/*.o grep/*.o gzip/*.o iconv/*.o lib/*.o patch/*.o procutils/*.o sed/*.o sharutils/*.o su/*.o util-linux/*.o which/*.o passwdutils/*.o

check:
	find -name '*.c' -or -name '*.h' | xargs cppcheck --std=c99 --check-level=exhaustive

init_outdir: o/bin o/sbin

o/bin:
	mkdir -p $@

o/sbin:
	mkdir -p $@

install: init_outdir
	PREFIX="$(PREFIX)" DESTDIR="$(DESTDIR)" scripts/install.sh

.PHONY: clean all init_outdir install check
