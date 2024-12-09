CC=sdcc -mz80 --code-loc 0 --data-loc 0 --no-std-crt0 --sdcccall 1
GHDL=ghdl-llvm
GHDL_ARGS=-fsynopsys --std=08 --workdir=build

all: build/boot.txt build/character_rom.txt
	mkdir -p build
	$(GHDL) -a $(GHDL_ARGS) T80/T80_Pack.vhd
	$(GHDL) -a $(GHDL_ARGS) T80/T80_ALU.vhd
	$(GHDL) -a $(GHDL_ARGS) T80/T80_MCode.vhd
	$(GHDL) -a $(GHDL_ARGS) T80/T80_Reg.vhd
	$(GHDL) -a $(GHDL_ARGS) T80/T80.vhd
	$(GHDL) -a $(GHDL_ARGS) T80/T80a.vhd
	$(GHDL) -a $(GHDL_ARGS) ram.vhd
	$(GHDL) -a $(GHDL_ARGS) rom.vhd
	$(GHDL) -a $(GHDL_ARGS) rom_async.vhd
	$(GHDL) -a $(GHDL_ARGS) T80a_testbench.vhd
	$(GHDL) -e $(GHDL_ARGS) T80a_testbench
	$(GHDL) -r $(GHDL_ARGS) T80a_testbench --stop-time=100ms --vcd=build/T80a_testbench.vcd

gtkwave:
	gtkwave build/T80a_testbench.vcd

view:
	cargo run --release --manifest-path viewer/Cargo.toml -- build/T80a_testbench.vcd

build/%.rel: %.asm
	mkdir -p build
	sdasz80 -o $@ $<

build/%.ihx: build/%.rel
	$(CC) -o $@ $<

build/%.bin: build/%.ihx
	objcopy -Iihex -Obinary --gap-fill=0x00 --pad-to=4096 $< $@

build/%.txt: build/%.bin
	xxd -b -c 1 $< | cut -d ' ' -f 2 > $@

build/character_rom.bin: ../roms/osborne1/7a3007-00.ud15
	cp -v $< $@

clean:
	rm -rf build
