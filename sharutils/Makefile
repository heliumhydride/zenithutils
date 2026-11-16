include ../config.mk

PROGS=shar uuencode uudecode

all: $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/bin/$(PROG_PREFIX)uuencode: OBJS = ../lib/util.o
../o/bin/$(PROG_PREFIX)uudecode: OBJS = ../lib/util.o

../o/bin/$(PROG_PREFIX)shar: shar.sh
	@echo "  COPY  $(notdir $@)"
	@cp $< $@

.PHONY: all $(PROGS)
