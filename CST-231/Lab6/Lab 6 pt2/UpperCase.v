module UpperCase(
input [7:0] din,
output reg [7:0] dout
);

always @(din)
begin
	if (din >  90)
		dout <= din - 32;
	else
		dout <= din;
	
end

endmodule
