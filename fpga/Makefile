CC=sdcc -mz80 --code-loc 0 --data-loc 0 --no-std-crt0 --sdcccall 1
GHDL_ARGS=-fsynopsys --std=08 --workdir=build

all: build/boot.txt build/character_rom.txt
	mkdir -p build
	ghdl -a $(GHDL_ARGS) T80/T80_Pack.vhd
	ghdl -a $(GHDL_ARGS) T80/T80_ALU.vhd
	ghdl -a $(GHDL_ARGS) T80/T80_MCode.vhd
	ghdl -a $(GHDL_ARGS) T80/T80_Reg.vhd
	ghdl -a $(GHDL_ARGS) T80/T80.vhd
	ghdl -a $(GHDL_ARGS) T80/T80a.vhd
	ghdl -a $(GHDL_ARGS) ram.vhd
	ghdl -a $(GHDL_ARGS) rom.vhd
	ghdl -a $(GHDL_ARGS) T80a_testbench.vhd
	ghdl -e $(GHDL_ARGS) T80a_testbench
	ghdl -r $(GHDL_ARGS) T80a_testbench --stop-time=34ms --vcd=build/T80a_testbench.vcd

gtkwave:
	gtkwave build/T80a_testbench.vcd

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