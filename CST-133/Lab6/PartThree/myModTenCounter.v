module myModTenCounter(
input clk, //clock input
input u_d, //up(0)/down(1)
input cen, //low active count enable
input reset, //reset input
output reg [3:0] q
);

always @ (posedge clk)
begin
if (reset)
 q <= 4'b0000; //reset
else if (cen) //hold value
	q <= q; //hold q value
else if (u_d) //count down
begin 
	if (q == 0) //if at lower limit
		q = 4'b1010; //set to highest limit
	q = q - 1; //subtract one
end
else if (~u_d) //count up
begin
if (q == 9) //if at upper limit
	q = 4'b1111; //set to lowest limit
q = q + 1; //add one

end

else
	q <= 4'b0000; 

end

endmodule