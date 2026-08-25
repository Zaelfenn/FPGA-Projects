module TopLevel(
input [3:0] a,
input [3:0] b,
output [3:0] sum,
output carryout
);
wire w1, w2, w3;
HalfAdder u1 (a[0], b[0], sum[0], w1);
FullAdder u2(w1, a[1], b[1], sum[1], w2);
FullAdder u3(w2, a[2], b[2], sum[2], w3);
FullAdder u4(w3, a[3], b[3], sum[3], carryout);

endmodule