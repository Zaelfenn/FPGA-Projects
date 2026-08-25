module TopLevel(
input clk, 
input rst, 
input din, 
output [6:0] lsb,				//'ones' hex digit
output [6:0] msb,				//'tens' hex digit
output err						//error bit, lights up LED
);

wire sm_clk;
wire [7:0] dout;

//115200 Hz
ClkDivider		#(162, 8)	c1(clk, rst, 1'b0, sm_clk);

//input clock, input reset, input data_in, output data_out, output error
UartRx					r1(sm_clk, rst, din, dout, err);

//input data_in, output data_out
SevenSegDecoder				ss1(dout[3:0], lsb);
SevenSegDecoder				ss2(dout[7:4], msb);

endmodule