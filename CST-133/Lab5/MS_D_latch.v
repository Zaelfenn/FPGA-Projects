module MS_D_latch( //master/slave D latch
input d, //input d
input clk, //clock
output q, //output one
output qnot //output two
);
wire w1, w2;

not u1 (w1, clk); //w3 = ~clk
Gated_D_latch u2 (d, w1, w2); //d = d, w1 = clk, w1 = q, w2 = qnot 
Gated_D_latch u3 (w2, clk, q, qnot); //w1 = d, clk = clk, q = q, qnot = qnot




endmodule