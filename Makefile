#!/usr/bin/make -R -r
# Copyright (C) 2026 H. Peter Anvin <hpa@zytor.com>

MAKEFLAGS += Rr

WHERE  := /opt/riscv/my
CROSS  := $(WHERE)/bin/

AS	= $(CROSS)as
LD	= $(CROSS)ld.lld
CC	= $(CROSS)clang
AR	= $(CROSS)llvm-ar
OBJCOPY	= $(CROSS)llvm-objcopy
PERL    = perl
HEXDUMP	= hexdump

SYSTEM ?= test
SYSDIR  = system/$(SYSTEM)

LDCFG   = $(SYSDIR)/link.ld

include riscv-opts.mk
-include $(SYSDIR)/*.mk

CFLAGS  = $(riscv_flags) -B '$(WHERE)' \
	-static -nostdlib -I./include
SFLAGS  = $(CFLAGS)
LDFLAGS	= $(CFLAGS) -fuse-ld='$(LD)' -Wl,-T,$(LDCFG) -Wl,-Map=$*.map \
	-Wl,--gc-sections -Wl,--relax -Wl,--relax-gp

TESTDIRS  = $(wildcard tests/*)
TESTS     = $(foreach d,$(TESTDIRS),$(d)/$(notdir $(d)).elf)
TESTNAMES = $(notdir $(TESTDIRS))
gendeps = -MD -MF .deps/$(subst /,.,$@).d -MT $@

TESTHEX  = $(TESTS:.elf=.tcm.hex) $(TESTS:.elf=.mem.hex)
BENCH    = bench

.SECONDARY:

.DELETE_ON_ERROR:

.PHONY: all tests bench run $(TESTNAMES) $(addprefix run-,$(TESTNAMES))

LIBDIRS := picos lib $(SYSDIR)/lib

GENSRC  = picos/irqtable.S

LIB	 = libpicos.a
LIBSRC  := $(shell find $(LIBDIRS) -type f -name '*.[cS]' -print) $(GENSRC)
LIBCSRC := $(filter %.c,$(LIBSRC))
LIBSSRC := $(filter %.S,$(LIBSRC))
LIBOBJS  = $(LIBCSRC:.c=.o) $(LIBSSRC:.S=.o)

all: tests lib

tests: $(TESTHEX)

lib: $(LIB)

bench:
	$(MAKE) -C $(BENCH)

run: $(addprefix run-,$(TESTNAMES))

define test-rule
$(1): tests/$(1)/$(1).tcm.hex tests/$(1)/$(1).mem.hex

run-$(1): $(1)
	$(MAKE) -C $(BENCH) run TEST=$(1) \
		TCM_INIT_FILE=$(abspath tests/$(1)/$(1).tcm.hex) \
		MEM_INIT_FILE=$(abspath tests/$(1)/$(1).mem.hex)
endef

$(foreach test,$(TESTNAMES),$(eval $(call test-rule,$(test))))

%.hex: %.bin
	$(HEXDUMP) -v -e '"" 8/4 "%08x " "\n"' $< > $@

%.tcm.bin: %.elf
	$(OBJCOPY) -O binary -R '.dram.*' $< $@

%.mem.bin: %.elf
	$(OBJCOPY) -O binary -j '.dram.*' $< $@

$(LIB): $(LIBOBJS)
	rm -f $@
	$(AR) rs $@ $^

.deps:
	mkdir -p $@

include/system:
	cd include && ln -sf ../$(SYSDIR)/include system

%.elf: $(LDCFG) $(LIB)
	$(CC) $(LDFLAGS) $(LDFLAGS_$@) -o $@ $(OBJS_$@) $(LIB)

builddeps := .deps include/system

%.o: %.S | $(builddeps)
	$(CC) $(SFLAGS) $(SFLAGS_$<) $(gendeps) -c -o $@ $<

%.s: %.S | $(builddeps)
	$(CC) $(SFLAGS) $(SFLAGS_$<) $(gendeps) -E -o $@ $<

%.o: %.c | $(builddeps)
	$(CC) $(CFLAGS) $(CFLAGS_$<) $(gendeps) -c -o $@ $<

%.s: %.c | $(builddeps)
	$(CC) $(CFLAGS) $(CFLAGS_$<) $(gendeps) -S -o $@ $<

%.i: %.c | $(builddeps)
	$(CC) $(SFLAGS) $(SFLAGS_$<) $(gendeps) -E -o $@ $<

picos/irqtable.S: picos/irqtable.pl
	$(PERL) $< > $@

clean:
	find . -type f \
		-regextype posix-extended \
		-regex '.*\.(hex|bin|elf|o|s|i|a)$$' -print0 \
		| xargs -0rt rm -f
	rm -rf $(builddeps) $(gensrc)

tests.d: $(TESTDIRS)
	( for d in $(TESTDIRS); do \
		e="$$d/$$(basename $$d).elf" ; \
		echo -n "OBJS_$$e =" ; \
		for s in "$$d"/*.[Sc]; do \
			echo -n " $${s/%.?/.o}" ; \
		done ; \
		echo '' ; \
		echo "$$e: \$$(OBJS_$$e)" ; \
	  done ) > $@

Makefile: tests.d

-include .deps/*.d
-include tests/*/*.mk
-include tests.d
