module TopLevel(
input clk,	
input rst,			//sw 0
input right,		//sw 1
input left,			//sw 2
input brake,		//sw 4
input hazard,		//sw 3
output [2:0] r_light,
output [2:0] l_light
);
wire sm_clk;

ClkDivider		#(25000000, 26)		c1(clk, rst, 1'b0, sm_clk);

LightController			sm1(sm_clk, rst, left, right, brake, hazard, r_light, l_light);

endmodule