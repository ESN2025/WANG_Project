library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity deco7seg is
    port (
        clk     : in  std_logic;
        reset   : in  std_logic;
        sel     : in  std_logic_vector(3 downto 0);
        segment : out std_logic_vector(7 downto 0)
    );
end entity deco7seg;

architecture description of deco7seg is
begin
    process(clk, reset)
    begin
        if reset = '0' then
            segment <= (others => '1');
        elsif rising_edge(clk) then
            case sel is
                when "0000" => 
                    segment <= "11000000"; -- 0
                when "0001" =>
                    segment <= "11111001"; -- 1
                when "0010" =>
                    segment <= "10100100"; -- 2
                when "0011" =>
                    segment <= "10110000"; -- 3
                when "0100" =>
                    segment <= "10011001"; -- 4
                when "0101" =>
                    segment <= "10010010"; -- 5
                when "0110" =>
                    segment <= "10000010"; -- 6
                when "0111" =>
                    segment <= "11111000"; -- 7
                when "1000" =>
                    segment <= "10000000"; -- 8
                when "1001" =>
                    segment <= "10010000"; -- 9

                when "1010" =>
                    segment <= "10111111"; 

                when others =>
                    segment <= "11111111"; 
            end case;
        end if;
    end process;
end architecture;
