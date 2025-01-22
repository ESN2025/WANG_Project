library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity top_lab3 is
    port (
        clk    : in  std_logic;
        reset_n: in  std_logic;

        -- ä¸‰ç»„7æ®µè¾“å‡º (ç™¾ä½, åä½, ä¸ªä½)
        seg_hund : out std_logic_vector(7 downto 0);
        seg_tens : out std_logic_vector(7 downto 0);
        seg_units: out std_logic_vector(7 downto 0)
    );
end entity;

architecture rtl of top_lab3 is

    ----------------------------------------------------------------------------
    -- 1) å£°æ˜Ž Qsys(Platform Designer) ç”Ÿæˆçš„ lab2_led3 ç»„ä»¶
    ----------------------------------------------------------------------------
    component lab3 is
        port (
            clk_clk                              : in  std_logic;
            reset_reset_n                        : in  std_logic;
            hund_pio_external_connection_export  : out std_logic_vector(3 downto 0);
            tens_pio_external_connection_export  : out std_logic_vector(3 downto 0);
            units_pio_external_connection_export : out std_logic_vector(3 downto 0)
        );
    end component lab3;

    ----------------------------------------------------------------------------
    -- 2) å£°æ˜Ž deco7seg (è¯‘ç æ¨¡å—)
    ----------------------------------------------------------------------------
    component deco7seg is
        port (
            clk     : in  std_logic;
            reset   : in  std_logic;
            sel     : in  std_logic_vector(3 downto 0);
            segment : out std_logic_vector(7 downto 0)
        );
    end component;

    ----------------------------------------------------------------------------
    -- 3) å®šä¹‰ä¿¡å·ï¼Œç”¨äºŽæŠŠlab2_led3çš„ä¸‰ç»„è¾“å‡ºè¿žåˆ°3ä¸ªè¯‘ç å™¨
    ----------------------------------------------------------------------------
    signal hund_sig : std_logic_vector(3 downto 0);
    signal tens_sig : std_logic_vector(3 downto 0);
    signal units_sig: std_logic_vector(3 downto 0);

begin

    ----------------------------------------------------------------------------
    -- å®žä¾‹åŒ– lab2_led3 (Qsysç³»ç»Ÿ)
    ----------------------------------------------------------------------------
    u0 : lab3
        port map (
            clk_clk         => clk,
            reset_reset_n   => reset_n,

            -- ä¸‰ä¸ª PIO(4ä½) ä»Ž CPU è¾“å‡º => VHDL è§†è§’ä¹Ÿå±žäºŽ "out"
            hund_pio_external_connection_export  => hund_sig,
            tens_pio_external_connection_export  => tens_sig,
            units_pio_external_connection_export => units_sig
        );

    ----------------------------------------------------------------------------
    -- å®žä¾‹åŒ– deco7seg ï¼Œå„è‡ªæ˜¾ç¤º hund/tens/units
    ----------------------------------------------------------------------------
    -- ç™¾ä½
    u_hund : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => hund_sig,
            segment => seg_hund
        );

    -- åä½
    u_tens : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => tens_sig,
            segment => seg_tens
        );

    -- ä¸ªä½
    u_units : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => units_sig,
            segment => seg_units
        );

end architecture rtl;