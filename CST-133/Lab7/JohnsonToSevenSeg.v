module JohnsonToSevenSeg(
input [4:0] q, //johnson counter input
output reg [6:0] light //seven seg output
);

always @ (q)
case(q)             //msb = seg 6, lsb = seg 0 
		5'd0 : light = 7'b1000000; //0, 5'b00000
		5'd1 : light = 7'b1111001; //1, 5'b00001
		5'd3 : light = 7'b0100100; //2, 5'b00011
		5'd7 : light = 7'b0110000; //3, 5'b00111
		5'd15 : light = 7'b0011001; //4, 5'b01111
		5'd31 : light = 7'b0010010; //5, 5'b11111
		5'd30 : light = 7'b0000010; //6, 5'b11110
		5'd28 : light = 7'b1111000; //7, 5'b11100
		5'd24 : light = 7'b0000000; //8, 5'b11000
		5'd16 : light = 7'b0010000; //9, 5'b10000
		default : light = 7'b1111111; //default to an off display
endcase

endmodule