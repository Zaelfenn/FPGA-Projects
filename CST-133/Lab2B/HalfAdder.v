module HalfAdder(
input a,
input b,
output sum,
output carryout
);

xor u1 (sum, a, b);
and u2 (carryout, a, b);

endmodule