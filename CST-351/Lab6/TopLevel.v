module TopLevel(
input clk,
input rst,
input car,
output [2:0] highway_light,
output [2:0] farm_light,
output uart_tx
);

wire traffic_clk, uart_clk, mem_clk, tx_ena;
wire [2:0] hw_light, f_light;
wire [5:0] addr;
wire [7:0] char;

ClkDivider #(25000000, 26) c1 (clk, rst, 1'b0, traffic_clk); //1 hz
ClkDivider #(2604, 12) c2 (clk, 1'b1, 1'b0, uart_clk); //9600 hz
//ClkDivider #(651, 10) c3 (clk, 1'b1, 1'b0, mem_clk); //38400 hz


traffic_vsm l1 (traffic_clk, car, rst, hw_light, f_light);

MemoryController ctrl1(uart_clk, rst, {car, hw_light, f_light}, addr, tx_ena);

myRom rom1(uart_clk, addr, char);
UartTx tx1 (uart_clk, 1'b1, char, tx_ena, uart_tx,);

assign highway_light = hw_light;
assign farm_light = f_light;
endmodule