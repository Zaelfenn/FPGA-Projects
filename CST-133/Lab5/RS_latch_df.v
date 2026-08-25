module RS_latch_df( //dataflow RS latch
input R, //input reset
input S, //input set
output q,  //output q
output qnot //output qnot
);

assign q = ~(qnot | S); //q = nor(qnot, s)
assign qnot = ~(q | R); //qnot = nor(q, r)

endmodule