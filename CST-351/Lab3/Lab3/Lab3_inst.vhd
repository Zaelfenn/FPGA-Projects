	component Lab3 is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			switches_export : in  std_logic_vector(9 downto 0) := (others => 'X'); -- export
			leds_export     : out std_logic_vector(9 downto 0)                     -- export
		);
	end component Lab3;

	u0 : component Lab3
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			switches_export => CONNECTED_TO_switches_export, -- switches.export
			leds_export     => CONNECTED_TO_leds_export      --     leds.export
		);

