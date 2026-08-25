module BCDto7seg(
input [3:0] dig,
output reg [6:0] light
);
//wire [6:0] temp;
always @ (dig)
begin
	case(dig)
		4'd0 : light = 7'b1000000;
		4'd1 : light = 7'b1111001;
		4'd2 : light = 7'b0100100;
		4'd3 : light = 7'b0110000;
		4'd4 : light = 7'b0011001;
		4'd5 : light = 7'b0011001;
		4'd6 : light = 7'b0000010;
		4'd7 : light = 7'b1111000;
		4'd8 : light = 7'b0000000;
		4'd9 : light = 7'b0010000;
		default: light = 7'b1111111;
		
	endcase
end
endmodule