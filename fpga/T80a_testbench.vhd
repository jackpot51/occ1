library ieee;
use ieee.numeric_std.all;
use ieee.std_logic_1164.all;
use std.textio.all;

entity T80a_testbench is
end T80a_testbench;

architecture behavior of T80a_testbench is
    -- Z80 pins
    signal RESET_n: std_logic := '0';
    signal R800_mode: std_logic := '0';
    signal CLK_N: std_logic := '0';
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
    -- Clocks
    signal CLK_62ns: std_logic := '0';
    signal CLK_DOT: std_logic := '1';
    signal CLK_MEM: std_logic := '0';
    signal CLK_CHAR: std_logic := '0';
    signal HSYNC: std_logic := '0';
    signal VSYNC: std_logic := '1';
    -- Row set to max value so it gets set to 0 on first clock pulse
    signal ROW: unsigned(8 downto 0) := to_unsigned(259, 9);
    -- Col set to max value so it gets set to 0 on first clock pulse
    signal COL: unsigned(9 downto 0) := to_unsigned(511, 10);
begin
    RESET_n <= '1' after 500 ns;
    CLK_62ns <= not CLK_62ns after 62 ns;

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

    -- Clocks

    clock_dot: process (CLK_62ns)
    begin
        if rising_edge(CLK_62ns) then
            CLK_DOT <= not CLK_DOT;
        end if;
    end process;

    clock_cpu: process (CLK_DOT)
    begin
        if rising_edge(CLK_DOT) then
            CLK_n <= not CLK_n;
        end if;
    end process;

    clock_mem: process(CLK_n)
    begin
        if falling_edge(CLK_n) then
            CLK_MEM <= not CLK_MEM;
        end if;
    end process;

    clock_char: process(CLK_MEM)
    begin
        if falling_edge(CLK_MEM) then
            CLK_CHAR <= not CLK_CHAR;
        end if;
    end process;

    video: process(CLK_DOT)
    begin
        if rising_edge(CLK_DOT) or falling_edge(CLK_DOT) then
            if (COL >= 511) then
                COL <= (others => '0');
                HSYNC <= '1';
                if (ROW >= 259) then
                    VSYNC <= '0';
                    ROW <= (others => '0');
                else
                    if (ROW = 19) then
                        VSYNC <= '1';
                    end if;
                    ROW <= ROW + 1;
                end if;
            else
                if (COL = 255) then
                    HSYNC <= '0';
                end if;
                COL <= COL + 1;
            end if;
        end if;
    end process;

    -- Serial

    stdout: process (CLK_n)
    begin
        if rising_edge(CLK_n) then
            if (MREQ_n = '0') then
                --if (RD_n = '0') then
                --    report "MEM READ " &
                --        to_hstring(ADDR) &
                --        " = " &
                --        to_hstring(DATA) &
                --        " '" &
                --        to_string(character'val(to_integer(unsigned(DATA)))) &
                --        "'";
                --end if;
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
