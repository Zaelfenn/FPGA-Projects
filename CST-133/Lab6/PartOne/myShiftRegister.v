module myShiftRegister(
input clk, //clock input
input [3:0] d, //input 
input sin, //shift in
input load, //overwriting load
input l_r, //left vs right shifts (left = 1, right = 0)
input reset, //reset to 0
output reg [3:0] q, //output
output reg sout //shift out
);

always @ (posedge clk or posedge reset)
begin
if (reset) //reset to 0
	q <= 4'b0000;
else if (load) //load value inputted
	q <= d;
else if (l_r) //left shift
begin
	q <= {q[2:0], sin}; //q shifts one left
	sout <= q[3]; //sout is the bit shifted out
end
else if (~l_r)
begin
	q <= {sin, q[3:1]}; //q shifts one left
	sout <= q[0]; //sout is the bit shifted out
end
else
	q <= 4'b0000;

end
endmodule