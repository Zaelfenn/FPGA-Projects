module FullAdder(
input carryin,
input a,
input b,
output sum,
output carryout
);
wire w1, w2, w3;
xor u1 (sum, carryin, a, b);
and u2 (w1, a, b);
and u3 (w2, a, carryin);
and u4 (w3, b, carryin);
or u5 (carryout, w1, w2, w3);

endmodule