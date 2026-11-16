include ../config.mk

# do we really need 'rename' and 'hardlink' ? (see 'mv' and 'ln')
# agetty not implemented, see nyagetty from chimera linux
# hwclock not being implemented for now
# losetup, pivot_root, ionice, write, show a "does not apply to windows" and return 1
# for mkswap/swapon/swapoff on windows: do we have functions in the win32 api to change pagefile settings ?
# for login on windows: use as a frontend to LogonUI/runas.exe maybe ? kind of a strech but I don't see what else login.exe would do...
# fsck on windows: do we just 'execvp("chkdsk.exe", ...);' ?

PROGS=rev uuidgen hexdump lscpu column blkid cal cfdisk chsh col dmesg eject fallocate findfs getopt ionice last login lsblk lslogins mcookie more mount mountpoint renice write whereis swapon swapoff
SPROGS=nologin fdisk fsck losetup mkfs mkswap mount pivot_root

all: $(PROGS) $(SPROGS)

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

../o/bin/$(PROG_PREFIX)rev: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)uuidgen: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)hexdump: OBJS = ../lib/util.o

../o/bin/$(PROG_PREFIX)uuidgen: LIBS = -lsodium

.PHONY: all $(PROGS) $(SPROGS)
