include ../config.mk

PROGS=which

all: $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

../o/bin/$(PROG_PREFIX)which: OBJS = ../lib/util.o

.PHONY: all $(PROGS)
