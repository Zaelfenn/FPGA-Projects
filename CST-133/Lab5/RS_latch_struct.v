module RS_latch_struct(
input R, //input reset
input S, //input set
output q, //output one
output qnot //output two
);


nor (q, S, qnot); //q takes input (set) and input (qnot)
nor (qnot, R, q);  //qnot takes input (reset) and input (qnot)


endmodule 