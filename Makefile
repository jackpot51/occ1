# Memory Map
# COM files start running at 0x100
# Data is placed at 0x2000 (TODO: does this actually work?)
# Optional I/O code is placed at 0x4000 (where bank 2 shadow starts)
# Stack is placed at 0x8000

CC=sdcc \
	-mz80 \
	--data-loc 0x2000 \
	--stack-loc 0x8000 \
	--no-std-crt0

# For example, -debug
MAMEFLAGS?=

# Single sided single density
FORMAT=osb1sssd

all: build/user.imd build/system.imd

build/%.com: build/%.ihx
	objcopy -Iihex -Obinary $< $@

build/%.rel: %.c
	mkdir -p build
	$(CC) -c -o $@ $<

build/%.ihx: %.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x108 -o $@ build/start.rel build/common.rel $<

build/beep.ihx: beep.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x4000 -o $@ build/start.rel build/common.rel $<

build/image.ihx: image.c build/start.rel build/common.rel occ1/program.asm
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x4000 -o $@ build/start.rel build/common.rel $<

build/system.img: roms/osborne1/os1syss.td0
	mkdir -p build
	rm -f $@.partial
	env HOME=$(PWD) dsktrans -itype tele -format $(FORMAT) -otype raw $< $@.partial
	cpmrm -f $(FORMAT) $@.partial autost.com
	mv $@.partial $@

build/user.img: build/beep.com build/game.com build/image.com build/physics.com
	rm -f $@.partial
	env HOME=$(PWD) dskform -type raw -format $(FORMAT) $@.partial
	mkfs.cpm -f $(FORMAT) $@.partial
	for file in $^; do \
	cpmcp -f $(FORMAT) $@.partial $$file 0:$$(basename $$file); \
	done
	mv $@.partial $@

build/%.img: build/%.com build/system.img
	cp -v build/system.img $@.partial
	cpmcp -f $(FORMAT) $@.partial $< 0:autost.com
	mv $@.partial $@

build/%.imd: build/%.img
	rm -f $@.partial
	env HOME=$(PWD) dsktrans -itype raw -format $(FORMAT) -otype imd $< $@.partial
	mv $@.partial $@

clean:
	rm -rf build

mame: build/user.imd build/system.imd
	mame osborne1 $(MAMEFLAGS) -window -rompath roms -floppydisk1 build/system.imd -floppydisk2 $<

mame_%: build/%.imd
	mame osborne1 $(MAMEFLAGS) -window -rompath roms -floppydisk1 $<
