
module Lab4 (
	clk_clk,
	pio_export,
	reset_reset_n,
	uart_rxd,
	uart_txd);	

	input		clk_clk;
	input	[7:0]	pio_export;
	input		reset_reset_n;
	input		uart_rxd;
	output		uart_txd;
endmodule
