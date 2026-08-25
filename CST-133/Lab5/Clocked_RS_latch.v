module Clocked_RS_latch( //RS latch with a clock
input clk, //clock input
input R, //reset input
input S, //set input
output q, //output q
output qnot //output qnot
);

wire w1, w2; //wires to connect

assign w1 = ~(clk & S); //input for S = clock nand S
assign w2 = ~(clk & R); //input for R = clock nand R

assign q = ~(w1 | qnot); 
assign qnot = ~(w2 | q); //RS_latch_df

endmodule 