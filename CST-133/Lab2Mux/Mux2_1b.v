module Mux2_1b (
input a,
input b,
input sel,
output mout
);
wire w1,w2, w3;

not u1 (w1, sel);
and u2 (w2, a, w1);
and u3 (w3, b, sel);
or u4 (mout, w2, w3);

endmodule