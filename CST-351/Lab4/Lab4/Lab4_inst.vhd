	component Lab4 is
		port (
			clk_clk       : in  std_logic                    := 'X';             -- clk
			pio_export    : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			reset_reset_n : in  std_logic                    := 'X';             -- reset_n
			uart_rxd      : in  std_logic                    := 'X';             -- rxd
			uart_txd      : out std_logic                                        -- txd
		);
	end component Lab4;

	u0 : component Lab4
		port map (
			clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
			pio_export    => CONNECTED_TO_pio_export,    --   pio.export
			reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
			uart_rxd      => CONNECTED_TO_uart_rxd,      --  uart.rxd
			uart_txd      => CONNECTED_TO_uart_txd       --      .txd
		);

