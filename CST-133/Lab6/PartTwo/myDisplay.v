module myDisplay(
input [3:0] d, //force load input
input u_d, //up one 0, down on 1
input clk, //clock input
input reset, //reset to 0
input load, //force load 

output [0:6] light //lights are active low
);

wire [3:0] q;
myCounter u1 (d, u_d, clk, reset, load, q);
myDecoder u2 (q, light);

endmodule


