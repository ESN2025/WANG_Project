library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity top_lab3 is
    port (
        clk       : in  std_logic;
        reset_n   : in  std_logic;

        scl_pad_io: inout std_logic;
        sda_pad_io: inout std_logic;

        btn       : in  std_logic;

        seg_sign  : out std_logic_vector(7 downto 0);
		  seg_thou  : out std_logic_vector(7 downto 0);
        seg_hund  : out std_logic_vector(7 downto 0);
        seg_tens  : out std_logic_vector(7 downto 0);
        seg_units : out std_logic_vector(7 downto 0)
    );
end entity top_lab3;

architecture rtl of top_lab3 is


    component lab3 is
        port (
            clk_clk         : in  std_logic;
            reset_reset_n   : in  std_logic;

            opencores_i2c_0_export_0_scl_pad_io : inout std_logic;
            opencores_i2c_0_export_0_sda_pad_io : inout std_logic;

            btn_pio_external_connection_export  : in  std_logic;
			   thou_pio_external_connection_export : out std_logic_vector(3 downto 0);
            sign_pio_external_connection_export : out std_logic_vector(3 downto 0);
            hund_pio_external_connection_export  : out std_logic_vector(3 downto 0);
            tens_pio_external_connection_export  : out std_logic_vector(3 downto 0);
            units_pio_external_connection_export : out std_logic_vector(3 downto 0)
        );
    end component;


    component deco7seg is
        port (
            clk     : in  std_logic;
            reset   : in  std_logic;
            sel     : in  std_logic_vector(3 downto 0);
            segment : out std_logic_vector(7 downto 0)
        );
    end component;


    signal sign_sig  : std_logic_vector(3 downto 0);
	 signal thou_sig  : std_logic_vector(3 downto 0);
    signal hund_sig  : std_logic_vector(3 downto 0);
    signal tens_sig  : std_logic_vector(3 downto 0);
    signal units_sig : std_logic_vector(3 downto 0);

begin

    u0 : lab3
        port map (
            clk_clk         => clk,
            reset_reset_n   => reset_n,

            opencores_i2c_0_export_0_scl_pad_io => scl_pad_io,
            opencores_i2c_0_export_0_sda_pad_io => sda_pad_io,

            btn_pio_external_connection_export  => btn,

            sign_pio_external_connection_export => sign_sig,
				thou_pio_external_connection_export => thou_sig,
            hund_pio_external_connection_export => hund_sig,
            tens_pio_external_connection_export => tens_sig,
            units_pio_external_connection_export => units_sig
        );


    u_sign : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => sign_sig,
            segment => seg_sign
        );
		  
    u_thou : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => thou_sig,     
            segment => seg_thou
        );

    u_hund : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => hund_sig,
            segment => seg_hund
        );

    u_tens : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => tens_sig,
            segment => seg_tens
        );

    u_units : deco7seg
        port map (
            clk     => clk,
            reset   => reset_n,
            sel     => units_sig,
            segment => seg_units
        );

end architecture rtl;
