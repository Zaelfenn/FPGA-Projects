module Decoder2x4 (
input ena,
input [1:0] x,
input p,
output [3:0] y
);
wire [3:0] w1;
wire [3:0] w2;

assign w1[0] = (~x[1] & ~x[0]);
assign w1[1] = (~x[1] & x[0]);
assign w1[2] = (x[1] & ~x[0]);
assign w1[3] = (x[1] & x[0]);

assign w2 = p ? (~w1):(w1);
assign y = ena ? (4'bzzzz):(w2);

endmodule