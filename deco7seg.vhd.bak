library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity deco7seg is
    port (
        clk     : in  std_logic;
        reset   : in  std_logic;
        sel     : in  std_logic_vector(3 downto 0);  
        segment : out std_logic_vector(7 downto 0)   -- (dp g f e d c b a)
    );
end entity deco7seg;

architecture description of deco7seg is
begin

    process(clk, reset)
    begin
        if reset = '0' then
            -- å½“ reset='0' æ—¶å¤ä½ï¼Œæ­¤å¤„è®©æ‰€æœ‰æ®µç†„ç­(å…±é˜³æž:1=ç­)
            segment <= (others => '1');
        elsif rising_edge(clk) then
            case sel is
                when "0000" => 
                    -- æ˜¾ç¤ºæ•°å­— 0
                    -- dp g f e d c b a = 1 1 0 0 0 0 0 0 = 0xC0
                    segment <= "11000000";
                when "0001" =>
                    -- æ˜¾ç¤ºæ•°å­— 1
                    segment <= "11111001"; -- 0xF9
                when "0010" =>
                    -- æ˜¾ç¤ºæ•°å­— 2
                    segment <= "10100100"; -- 0xA4
                when "0011" =>
                    -- æ˜¾ç¤ºæ•°å­— 3
                    segment <= "10110000"; -- 0xB0
                when "0100" =>
                    -- æ˜¾ç¤ºæ•°å­— 4
                    segment <= "10011001"; -- 0x99
                when "0101" =>
                    -- æ˜¾ç¤ºæ•°å­— 5
                    segment <= "10010010"; -- 0x92
                when "0110" =>
                    -- æ˜¾ç¤ºæ•°å­— 6
                    segment <= "10000010"; -- 0x82
                when "0111" =>
                    -- æ˜¾ç¤ºæ•°å­— 7
                    segment <= "11111000"; -- 0xF8
                when "1000" =>
                    -- æ˜¾ç¤ºæ•°å­— 8
                    segment <= "10000000"; -- 0x80
                when "1001" =>
                    -- æ˜¾ç¤ºæ•°å­— 9
                    segment <= "10010000"; -- 0x90
                when others =>
                    -- å…¨éƒ¨ç†„ç­(å«dp)
                    -- dp g f e d c b a = 1 1 1 1 1 1 1 1 = 0xFF
                    segment <= "11111111";
            end case;
        end if;
    end process;

end architecture;