module mux(
input clk,
input rst,
input b1, 		//busy 1
input b2, 		//busy 2
input o1, 		//output from uart 1
input o2,		//output from uart 2
output reg dout		//output 
);


always @ (posedge clk)
begin
if (rst)
	dout <= 1'b1;
else if (b1)
	dout <= o1;
else if (b2)
	dout <= o2;
else
	dout <= 1'b1;

end


endmodule