include ../config.mk

PROGS=patch

all: $(PROGS)

$(PROGS): %: ../o/bin/$(PROG_PREFIX)%
$(SPROGS): %: ../o/sbin/$(PROG_PREFIX)%

%.o: %.c ../config.h
	@echo "  CC    $(notdir $@)"
	@$(CC) $(CFLAGS) -DPROG_PREFIX=\"$(PROG_PREFIX)\" -c $< -o $@

.SECONDEXPANSION:

../o/bin/$(PROG_PREFIX)%: %.o $$(OBJS)
	@echo "  LD    $(notdir $@)"
	@$(LD) $(LDFLAGS) $^ -o $@ $(LIBS)

.PHONY: all $(PROGS)
