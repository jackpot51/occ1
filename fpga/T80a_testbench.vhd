library ieee;
use ieee.std_logic_1164.all;

entity T80a_testbench is
end T80a_testbench;

architecture behavior of T80a_testbench is
    component T80a is
        port (
            RESET_n  : in  std_logic;
            CLK_n  : in  std_logic
        );
    end component;
    signal input  : std_logic_vector(2 downto 0);
    signal output : std_logic_vector(1 downto 0);
begin
    uut: T80a port map (
        RESET_n => input(0),
        CLK_n => input(1)
    );

    stim_proc: process
    begin
        --input <= "000"; wait for 10 ns; assert output = "00" report "0+0+0 failed";
        report "T80a testbench finished";
        wait;
    end process;
end;