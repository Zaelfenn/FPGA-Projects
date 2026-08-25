module dstorage(
input d,
input clk,
output [2:0] q
);

dlatch_BH u1 (d, clk, q[0]);
dff_pos_BH u2 (d, clk, q[1]);
dff_neg_BH u3(d, clk, q[2]);

endmodule