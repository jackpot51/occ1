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

all: build/example.imd

build/%.com: build/%.ihx
	objcopy -Iihex -Obinary $< $@

build/%.rel: %.c
	mkdir -p build
	$(CC) -c -o $@ $<

build/%.ihx: %.c build/start.rel build/common.rel occ1/program.asm
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x108 -o $@ build/start.rel build/common.rel $<

build/beep.ihx: beep.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x4000 -o $@ build/start.rel build/common.rel $<

build/image.ihx: image.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -Wl-b_START=0x100 --code-loc 0x4000 -o $@ build/start.rel build/common.rel $<

build/example.img: build/beep.com build/game.com build/image.com build/physics.com
	rm -f $@.partial
	env HOME=$(PWD) dskform -type raw -format osb1sssd $@.partial
	mkfs.cpm -f osb1sssd $@.partial
	for file in $^; do \
	cpmcp -f osb1sssd $@.partial $$file 0:$$(basename $$file); \
	done
	mv $@.partial $@

build/example.imd: build/example.img
	rm -f $@.partial
	env HOME=$(PWD) dsktrans -itype raw -format osb1sssd -otype imd $< $@.partial
	mv $@.partial $@

clean:
	rm -rf build

mame: build/example.imd
	mame osborne1 -window -rompath roms -floppydisk1 roms/osborne1/os1syss.td0 -floppydisk2 $<

mame_debug: build/example.imd
	mame osborne1 -debug -window -rompath roms -floppydisk1 roms/osborne1/os1syss.td0 -floppydisk2 $<

run: build/physics.com
	cargo build --release --manifest-path iz-cpm/Cargo.toml
	iz-cpm/target/release/iz-cpm --slow $<
