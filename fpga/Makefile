 GHDL_ARGS=-fsynopsys --workdir=build

 all:
	mkdir -p build
	ghdl -a $(GHDL_ARGS) t80/T80_Pack.vhd
	ghdl -a $(GHDL_ARGS) t80/T80a.vhd
	ghdl -a $(GHDL_ARGS) T80a_testbench.vhd
	ghdl -e $(GHDL_ARGS) T80a_testbench
	ghdl -r $(GHDL_ARGS) T80a_testbench --vcd=build/T80a_testbench.vcd
	gtkwave build/T80a_testbench.vcd

clean:
	rm -rf build