ifeq ($(wildcard config.mk),)
  $(error Please run ./configure first..)
endif

include config.mk

SUBDIRS = customtools coreutils util-linux which procutils diffutils findutils grep gzip iconv patch sed sharutils su passwdutils

all: $(SUBDIRS)

customtools:
	$(MAKE) -C customtools

coreutils:
	$(MAKE) -C coreutils

util-linux:
	$(MAKE) -C util-linux

which:
	$(MAKE) -C which

procutils:
	$(MAKE) -C procutils

diffutils:
	$(MAKE) -C diffutils

findutils:
	$(MAKE) -C findutils

grep:
	$(MAKE) -C grep

gzip:
	$(MAKE) -C gzip

iconv:
	$(MAKE) -C iconv

patch:
	$(MAKE) -C patch

sed:
	$(MAKE) -C sed

sharutils:
	$(MAKE) -C sharutils

su:
	$(MAKE) -C su

passwdutils:
	$(MAKE) -C passwdutils

install: 
	PREFIX="$(PREFIX)" DESTDIR="$(DESTDIR)" scripts/install.sh

clean:
	rm -rf o/bin/* o/sbin/* coreutils/*.o customtools/*.o diffutils/*.o findutils/*.o grep/*.o gzip/*.o iconv/*.o lib/*.o patch/*.o procutils/*.o sed/*.o sharutils/*.o su/*.o util-linux/*.o which/*.o passwdutils/*.o

distclean: clean
	rm -rf config.h config.mk o/

check:
	find -name '*.c' -or -name '*.h' | xargs cppcheck --std=c99 --check-level=exhaustive >/dev/null
	shellcheck -S style -s sh scripts/* configure

tags:
	ctags -R --c-kinds=+p --exclude=TODO --exclude=docs --exclude=o --exclude=scripts --exclude=README.md

.PHONY: all $(SUBDIRS) clean distclean install check tags all customtools
