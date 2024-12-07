library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
use std.textio.all;

entity T80a_testbench is
end T80a_testbench;

architecture behavior of T80a_testbench is
    signal RESET_n: std_logic := '1';
    signal R800_mode: std_logic := '0';
    signal CLK_N: std_logic := '1';
    signal WAIT_n: std_logic := '1';
    signal INT_n: std_logic := '1';
    signal NMI_n: std_logic := '1';
    signal BUSRQ_n: std_logic := '1';
    signal MREQ_n: std_logic;
    signal IORQ_n: std_logic;
    signal RD_n: std_logic;
    signal WR_n: std_logic;
    signal ADDR: std_logic_vector(15 downto 0);
    signal DATA: std_logic_vector(7 downto 0);
begin
    RESET_n <= '0', '1' after 500 ns;
    CLK_n <= not CLK_n after 125 ns;

    z80a: entity work.T80a port map (
        RESET_n => RESET_n,
        R800_mode => R800_mode,
        CLK_n => CLK_n,
        WAIT_n => WAIT_n,
        INT_n => INT_n,
        NMI_n => NMI_n,
        BUSRQ_n => BUSRQ_n,
        MREQ_n => MREQ_n,
        IORQ_n => IORQ_n,
        RD_n => RD_n,
        WR_n => WR_n,
        A => ADDR,
        D => DATA
    );

    rom: entity work.rom port map (
        CLK_n => CLK_n,
        RD_n => RD_n,
        ADDR => ADDR,
        DATA => DATA
    );

    stdout: process (CLK_n)
    begin
        if rising_edge(CLK_n) then
            if (MREQ_n = '0') then
                if (RD_n = '0') then
                    report "MEM READ " &
                        to_hstring(ADDR) &
                        " = " &
                        to_hstring(DATA) &
                        " '" &
                        to_string(character'val(to_integer(unsigned(DATA)))) &
                        "'";
                end if;
                if (WR_n = '0') then
                    report "MEM WRITE " &
                        to_hstring(ADDR) &
                        " = " &
                        to_hstring(DATA) &
                        " '" &
                        to_string(character'val(to_integer(unsigned(DATA)))) &
                        "'";
                end if;
            end if;
            if (IORQ_n = '0') then
                if (RD_n = '0') then
                    report "IO READ " &
                        to_hstring(ADDR) &
                        " = " &
                        to_hstring(DATA) &
                        " '" &
                        to_string(character'val(to_integer(unsigned(DATA)))) &
                        "'";
                end if;
                if (WR_n = '0') then
                    report "IO WRITE " &
                        to_hstring(ADDR) &
                        " = " &
                        to_hstring(DATA) &
                        " '" &
                        to_string(character'val(to_integer(unsigned(DATA)))) &
                        "'";
                end if;
            end if;
        end if;
    end process;
end;
