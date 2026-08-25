module TopLevel(
	input clk,
	input rst,
	input rx_in,
	input tx_start,
	input [7:0] switch_in,
	output tx_out,
	output [7:0] led_out,
	output tx_clk_out
);
wire tx_clk, rx_clk, tx_busy, err;
ClkDivider #(1302,11) tx_c  (clk, rst, 1'b0, tx_clk); //9600
ClkDivider #(81,7) rx_c  (clk, rst, 1'b0, rx_clk); //153600

UartTx tx (tx_clk, rst, switch_in, tx_start, tx_out, tx_busy);
UartRx rx (rx_clk, rst, rx_in, led_out, err);
not u1 (tx_clk_out, tx_clk);

endmodule