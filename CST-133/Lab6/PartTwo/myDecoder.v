module myDecoder(
input [3:0] q, //input to display
output reg [0:6] light //lights are active low
);
always @ (q)
begin
case (q)
4'd0 : light = 7'b1000000;
4'd1 : light = 7'b1111001;
4'd2 : light = 7'b0100100;
4'd3 : light = 7'b0110000;
4'd4 : light = 7'b0011001;
4'd5 : light = 7'b0010010;
4'd6 : light = 7'b0000010;
4'd7 : light = 7'b1111000;
4'd8 : light = 7'b0000000;
4'd9 : light = 7'b0011000;
4'd10: light = 7'b0001000;
4'd11: light = 7'b0000011;
4'd12: light = 7'b1000110;
4'd13: light = 7'b0100001;
4'd14: light = 7'b0000110;
4'd15: light = 7'b0001110;
default: light = 7'b1111111;
endcase
end

endmodule