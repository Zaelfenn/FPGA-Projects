module Gated_D_latch( //gated D latch
input d, //input
input clk, //clock
output q, //output q
output qnot //output qnot
);

wire w1, w2;

assign w1 = ~(d & clk); //first input is d nand clock
assign w2 = ~(~d & clk); //second input is nd nand clock

assign q = ~(w1 & qnot); //first output is input_one nand qnot
assign qnot = ~(w2 & q); //second output is input_two nand q

endmodule