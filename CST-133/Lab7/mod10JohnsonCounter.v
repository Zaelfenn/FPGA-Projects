module mod10JohnsonCounter(
input cen, //count enable, 1 = count, 0 = hold
input u_d, //up on one, down on 0
input clk, //clock
input rst, //reset
output reg [4:0] q //output
);

always @ (posedge clk)
begin

if (rst) //reset
	q <= 5'b00000;
else if (~cen) //count enable
	q <= q;
else if (u_d) //count down
	case(q)
	5'b00000 : q <= 5'b10000; //0 : 9
	5'b00001 : q <= 5'b00000; //1 : 0
	5'b00011 : q <= 5'b00001; //2 : 1
	5'b00111 : q <= 5'b00011; //3 : 2
	5'b01111 : q <= 5'b00111; //4 : 3
	5'b11111 : q <= 5'b01111; //5 : 4
	5'b11110 : q <= 5'b11111; //6 : 5
	5'b11100 : q <= 5'b11110; //7 : 6
	5'b11000 : q <= 5'b11100; //8 : 7
	5'b10000 : q <= 5'b11000; //9 : 8
	default : q <= 5'b00000; //default to 0
	endcase
else if (~u_d) //count up
	case (q)
	5'b00000 : q <= 5'b00001; //0 : 1
	5'b00001 : q <= 5'b00011; //1 : 2
	5'b00011 : q <= 5'b00111; //2 : 3
	5'b00111 : q <= 5'b01111; //3 : 4
	5'b01111 : q <= 5'b11111; //4 : 5
	5'b11111 : q <= 5'b11110; //5 : 6
	5'b11110 : q <= 5'b11100; //6 : 7
	5'b11100 : q <= 5'b11000; //7 : 8
	5'b11000 : q <= 5'b10000; //8 : 9
	5'b10000 : q <= 5'b00000; //9 : 0
	endcase	
else 
	q <= 0;
 
end
endmodule