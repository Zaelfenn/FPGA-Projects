module bcd_counter_to_display(
input clk, //clock input
input u_d, //up(0)/down(1)
input cen, //low active count enable
input reset, //reset input
output [6:0] q
);
wire [3:0] temp;

myModTenCounter u1 (clk, u_d, cen, reset, temp);
myBCDDec u2 (temp, q);

endmodule