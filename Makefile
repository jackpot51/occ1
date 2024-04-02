all: build/example.imd

build/%.com: build/%.ihx
	objcopy -Iihex -Obinary $< $@

build/%.ihx: %.c occ1/program.asm
	mkdir -p build
	sdcc \
		-mz80 \
		--code-loc 0x100 \
		--data-loc 0x2000 \
		--stack-loc 0x4000 \
		--no-std-crt0 \
		-o $@ \
		$<

build/example.img: build/occ1demo.com build/physics.com
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
	mame osborne1 -debug -rompath roms -floppydisk1 cpm22 -floppydisk2 $<

run: build/physics.com
	cargo build --release --manifest-path iz-cpm/Cargo.toml
	iz-cpm/target/release/iz-cpm --slow $<
