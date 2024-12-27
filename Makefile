# Memory Map
# COM files start running at 0x100
# Optional I/O code is placed at 0x4000 (where bank 2 shadow starts)
# Stack is placed at 0xC800

CC=sdcc \
	-mz80 \
	--stack-loc 0xC800 \
	--no-std-crt0 \
	--sdcccall 1

# For example, -debug
#MAMEFLAGS?=-video bgfx -bgfx_screen_chains crt-geom-deluxe
MAMEFLAGS?=-nounevenstretch

# Single sided single density
FORMAT=osb1sssd

all: build/user.imd build/system.imd

kermit:
	sudo kermit -b 1200 -l /dev/ttyUSB0 -C "set flow-control none, set carrier-watch off"

build/%.com: build/%.ihx
	objcopy -Iihex -Obinary $< $@

build/%.rel: %.asm
	mkdir -p build
	sdasz80 -o $@ $<

build/%.rel: %.c
	mkdir -p build
	$(CC) -c -o $@ $<

build/%.ihx: %.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -o $@ build/start.rel build/common.rel $<

build/beep.ihx: beep.c build/start.rel build/common.rel
	mkdir -p build
	$(CC) -Wl-b_BEEP=0x4000 -o $@ build/start.rel build/common.rel $<

build/image-left.asm: occ1/res/occ1-left.jpg occ1/src/main.rs
	mkdir -p build
	cargo run --release --manifest-path occ1/Cargo.toml -- --new-algo --no-show $< $@ 22 18 0x16 0

build/image-middle.asm: occ1/res/occ1-right.jpg occ1/src/main.rs
	mkdir -p build
	cargo run --release --manifest-path occ1/Cargo.toml -- --new-algo --no-show $< $@ 22 18 0x16 17

build/image-right.asm: occ1/res/osborne.png occ1/src/main.rs
	mkdir -p build
	cargo run --release --manifest-path occ1/Cargo.toml -- --new-algo --no-show $< $@ 22 27 0x16 34

build/image.ihx: image.c build/start.rel build/common.rel build/irq1.rel build/image-left.asm build/image-middle.asm build/image-right.asm
	mkdir -p build
	$(CC) -Wl-b_IRQ1=0xC000 -o $@ build/start.rel build/common.rel $< build/irq1.rel

build/rickroll.ihx: rickroll.c build/start.rel build/common.rel build/irq1.rel occ1/build/frame-*.asm
	mkdir -p build
	$(CC) -Wl-b_IRQ1=0xC000 -o $@ build/start.rel build/common.rel $< build/irq1.rel

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
	cpmrm -f $(FORMAT) $@.partial '*.com'
	cpmcp -f $(FORMAT) $@.partial $< 0:autost.com
	mv $@.partial $@

build/%.imd: build/%.img
	rm -f $@.partial
	env HOME=$(PWD) dsktrans -itype raw -format $(FORMAT) -otype imd $< $@.partial
	mv $@.partial $@

build/%.td0: build/%.img
	rm -f $@.partial
	env HOME=$(PWD) dsktrans -itype raw -format $(FORMAT) -otype tele $< $@.partial
	mv $@.partial $@

clean:
	rm -rf build

mame: build/user.imd build/system.imd
	mame osborne1 $(MAMEFLAGS) -window -rompath roms -floppydisk1 build/system.imd -floppydisk2 $<

mame_%: build/%.imd
	mame osborne1 $(MAMEFLAGS) -window -rompath roms -floppydisk1 $<
