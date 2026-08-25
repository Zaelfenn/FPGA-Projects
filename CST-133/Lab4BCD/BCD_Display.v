module BCD_Display(
input [3:0] a,
input [3:0] b,
output [6:0] ones,
output [6:0] tens
);

wire [7:0] temp;

BCD_ADDER	u1	(a,b, temp);
BCDto7seg	u2	(temp[3:0], ones);
BCDto7seg	u3	(temp[7:4], tens);

endmodule