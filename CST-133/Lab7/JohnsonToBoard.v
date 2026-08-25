module JohnsonToBoard(
input cen, //count enable, 1 = count, 0 = hold
input u_d, //up on one, down on 0
input clk, //clock
input rst, //reset
output [6:0] light //output of johnsontosevenseg
);
wire [4:0]q;//output of mod10johnsoncounter

mod10JohnsonCounter u1 (cen, u_d, clk, rst, q);
JohnsonToSevenSeg u2 (q, light);



endmodule