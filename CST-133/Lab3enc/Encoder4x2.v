module Encoder4x2(
input ena,
input [3:0] x,
output [1:0] r,
output valid
);
wire [1:0] v;
assign v[0] = ~ena & ~x[0] & ~x[1] & ~x[2] & ~x[3];
assign v[1] = ena;
assign valid = v[1] | v[0];

assign r[0] = ena?(0):((x[1] & ~x[2]) | x[3]);
assign r[1] = ena?(0):(x[2] | x[3]);


endmodule