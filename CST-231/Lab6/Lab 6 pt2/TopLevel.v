module TopLevel(
input clk,
input rst, 
input din,
output dout
);

wire [7:0] uc_out;
wire [7:0] rx_out;
wire start, err, busy;
//clock for UART receiver
ClkDivider	#(162, 8)			c1(clk, rst, 1'b0, rx_clk);

//clock for UART transmitter
ClkDivider	#(2603, 12)			c2(clk, rst, 1'b0, tx_clk);

UartRx					u1(rx_clk, rst, din, rx_out, err, start);

UpperCase				uc(rx_out, uc_out);

UartTx					u2(tx_clk, rst, uc_out, start, dout, busy);



endmodule