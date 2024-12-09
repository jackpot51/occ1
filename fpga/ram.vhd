-- From https://github.com/dominiksalvet/vhdl-collection/blob/master/rtl/rom.vhdl
--------------------------------------------------------------------------------
-- Copyright (C) 2016-2018 Dominik Salvet
-- SPDX-License-Identifier: MIT
--------------------------------------------------------------------------------
-- Compliant: IEEE Std 1076-1993
-- Target:    independent
--------------------------------------------------------------------------------
-- Description:
--     Generic implementation of a single port synchronous ROM memory with
--     initialization from a file or a linear initialization where memory
--     content is [address]=address.
--------------------------------------------------------------------------------
-- Notes:
--     1. Since there is a read enable signal, DATA output will be implemented
--        as a register.
--     2. The module can be implemented as a block memory, if the target
--        platform and used synthesizer support it.
--     3. If it is required to use a linear initialization, set the
--        g_MEM_IMG_FILENAME generic to "".
--     4. If the initialization from a file will be used, the file must contain
--        only ASCII "0" and "1" characters, each line's length must be equal to
--        set g_DATA_WIDTH and file must have 2**g_ADDR_WIDTH lines.
--------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

library std;
use std.textio.all;

entity ram is
    generic (
        g_ADDR_WIDTH : positive := 16; -- bit width of RAM address bus
        g_DATA_WIDTH : positive := 8 -- bit width of RAM data bus
    );
    port (
        CLK_n : in std_logic; -- clock signal
        
        RD_n   : in  std_logic; -- read enable
        WR_n   : in  std_logic; -- write enable
        ADDR : in  std_logic_vector(g_ADDR_WIDTH - 1 downto 0); -- address bus
        DATA : out std_logic_vector(g_DATA_WIDTH - 1 downto 0) -- output data bus
    );
end entity;


architecture rtl of ram is
    -- definition of the used memory type
    type t_MEM is array(0 to integer((2 ** g_ADDR_WIDTH) - 1)) of
        std_logic_vector(g_DATA_WIDTH - 1 downto 0);
    
    signal MEM: t_MEM := (
        others => (others => '0')
    );
begin
    -- Description:
    --     Memory read/write mechanism description.
    mem_rw : process (CLK_n) is
    begin
        if (rising_edge(CLK_n)) then
            if (RD_n = '0') then
                DATA <= MEM(to_integer(unsigned(ADDR)));
            else
                if (WR_n = '0') then
                    MEM(to_integer(unsigned(ADDR))) <= DATA;
                else
                    DATA <= (others => 'Z');
                end if;
            end if;
        end if;
    end process;
end architecture;