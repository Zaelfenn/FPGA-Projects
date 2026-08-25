module Lab2 (
input wire[3:0] a,
input wire[3:0] b,
input sel,
output wire[3:0] mout
);

Mux2_1b u1 (a[0], b[0], sel, mout[0]);
Mux2_1b u2 (a[1], b[1], sel, mout[1]);
Mux2_1b u3 (a[2], b[2], sel, mout[2]);
Mux2_1b u4 (a[3], b[3], sel, mout[3]);

endmodule 