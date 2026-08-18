ifeq ($(wildcard config.mk),)
  $(error Please run ./configure first..)
endif

include config.mk

SUBDIRS = customtools coreutils util-linux which procutils diffutils findutils grep gzip iconv patch sed sharutils su passwdutils

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

install: 
	PREFIX="$(PREFIX)" DESTDIR="$(DESTDIR)" scripts/install.sh

clean:
	rm -f o/bin/* o/sbin/*
	rm -f lib/*.o
	for x in $(SUBDIRS); do \
		rm -f $$x/*.o; \
	done

distclean: clean
	rm -rf config.h config.mk o/

check:
	find -name '*.c' -or -name '*.h' | xargs cppcheck --std=c99 --check-level=exhaustive
	shellcheck -S style -s sh scripts/* configure

tags:
	ctags -R --c-kinds=+p --exclude=TODO --exclude=docs --exclude=o --exclude=scripts --exclude=README.md

.PHONY: all $(SUBDIRS) clean distclean install check tags
