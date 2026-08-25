module TopLevel(
input clk,
input rst,
input key0,
input key1,
input [7:0] din,
output dout
);

wire div_clk, sw_busy, sw_ena, sw_out,code_busy, code_ena, code_out;	//single bit inputs 
wire [7:0] sw_char;		//output for characters on the switch
wire [7:0] char;			//output for characters in the code
wire [7:0] code_char;	//temporary placeholder for characters in the code

//param: count, bits for count			//in sysclk, in rst, in enable, out div clk
ClkDivider	#(2603, 12)			clock(clk, rst, 1'b0, div_clk);

//in clk, in rst, in busy, in button, in char, out char, out enable
ButtonCheck							b0(div_clk, rst, sw_busy, key0, din, sw_char, sw_ena);
ButtonCheck							b1(div_clk, rst, code_busy, key1, code_char, char, code_ena);

//in clk, in rst, in enable, out char
NameOut								z1(div_clk, rst, code_ena, code_char);

//in clk, in rst, in char, in enable, out data, out busy
UartTx								u0(div_clk, rst, din, sw_ena, sw_out, sw_busy);
UartTx								u1(div_clk, rst, char, code_ena, dout, code_busy);


endmodule