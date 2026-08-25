module BCD_ADDER(
input [3:0] a,
input [3:0] b,
output [7:0] out
);

assign out = (a + b > 9) ? (a + b + 6) : a + b;


endmodule