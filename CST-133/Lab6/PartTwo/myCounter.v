module myCounter(
input [3:0] d, //force load input
input u_d, //up one 0, down on 1
input clk, //clock input
input reset, //reset to 0
input load, //force load 

output reg [3:0] q
);

always @ (posedge clk)
begin

if (reset)
	q <= 4'b0000;
else if (load)
	q <= d;
else if (u_d)
	q <= q - 1;
else if (~u_d)
	q <= q + 1;
else
	q <= 4'b0000;

end

endmodule