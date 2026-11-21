include ../config.mk

# logname is a link to whoami
# md5sum is a link to md5
# [ is a link to test
# TODO how would 'nohup' work on Windows?

PROGS=cat nproc ls uname seq pwd true false yes dirname basename tac sleep wc mktemp tty base64 base32 mkdir rmdir test whoami readlink dos2unix unix2dos head echo tee shred rm sha512sum tail hostname factor uniq tr date mkfifo cp mv sync sort touch timeout truncate users nice ln install id groups df chroot chmod chown cut dd fmt fold md5 sha1sum sha224sum sha256sum sha384sum pr chgrp comm du env expand expr join od printf split stty tsort unexpand who nl ed printenv nohup numfmt paste pathchk finger realpath stat shuf
SPROGS=
ifeq ($(WIN32), 0)
	SPROGS += mknod
endif

all: $(SPROGS) $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%
$(SPROGS): %: ../o/sbin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/sbin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/bin/$(PROG_PREFIX)dos2unix: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)cat: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)ls: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)uname: OBJS = ../lib/util.o ../lib/utsname_winnt.o
../o/bin/$(PROG_PREFIX)seq: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)pwd: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)tac: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)sleep: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)wc: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)tr: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)base64: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)base32: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)mktemp: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)whoami: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)test: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)uniq: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)mkdir: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)rmdir: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)head: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)tail: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)readlink: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)tee: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)shred: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)rm: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)sha512sum: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)hostname: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)factor: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)touch: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)date: OBJS = ../lib/util.o
../o/sbin/$(PROG_PREFIX)mknod: OBJS = ../lib/util.o

../o/bin/$(PROG_PREFIX)base64: LIBS = -lsodium
../o/bin/$(PROG_PREFIX)mktemp: LIBS = -lsodium
../o/bin/$(PROG_PREFIX)shred:  LIBS = -lsodium
../o/bin/$(PROG_PREFIX)sha512sum:  LIBS = -lsodium

../o/bin/$(PROG_PREFIX)unix2dos: ../o/bin/$(PROG_PREFIX)dos2unix
ifeq ($(WIN32), 1)
	@echo "  COPY  $(notdir $(@).exe)"
	@cp $<.exe $@.exe
else
	@echo "  COPY  $(notdir $@)"
	@cp $< $@
endif

.PHONY: all $(PROGS) $(SPROGS)
