library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

entity TopLevel is
	port(clk, rst, haz, brake, turn_left, turn_right : in std_logic;
			r_light, l_light: out std_logic_vector(0 to 2));
end TopLevel;

architecture structural of TopLevel is 
	component ClockDivider
		generic (DIV: natural:=12500000);
		port ( clk,reset: in std_logic;
		clock_out: out std_logic);
	end component;
	component TaillightsController
		port(clk,reset,haz,brake,turn_left,turn_right: in std_logic;
		r_light,l_light: out std_logic_vector(0 to 2) 	);
	end component;
	signal div_clk : std_logic := '0';
	constant div : natural := 12500000;
	
	begin
		c1: ClockDivider generic map (DIV => div) port map (clk => clk, reset => rst, clock_out => div_clk);
		t1: TaillightsController port map (clk => div_clk, reset => rst, haz => haz, brake => brake, turn_left => turn_left, turn_right => turn_right, r_light => r_light, l_light => l_light);
	end structural;