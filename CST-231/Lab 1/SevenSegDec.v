module SevenSegDec(
input [4:0] qin, 						//highest amount of bits that will be input is 5
output reg [6:0] light_ones, 		//the segments that should be lit up for the ones place (active low seven seg)- reading from msb(as pos. 0) to lsb (as pos. 6)
output reg [6:0] light_tens		//the segments that should be lit up for the tens place (active low seven seg)
);

always @ (qin)
begin

case (qin)
	5'b00000:				//0
		begin					//zero is 0,1,2,3,4,5
		light_ones = 7'b0000001; //zero
		light_tens = 7'b0000001; //zero
		end
	5'b00001:				//1
		begin					//one is 1,2
		light_ones = 7'b1001111; //one
		light_tens = 7'b0000001; //zero
		end
	5'b00010:				//2
		begin					//two is 0,1,3,4,6
		light_ones = 7'b0010010; //two
		light_tens = 7'b0000001; //zero
		end
	5'b00011:				//3
		begin					//three is 0,1,2,3,6
		light_ones = 7'b0000110; //three
		light_tens = 7'b0000001; //zero
		end
	5'b00100:				//4
		begin					//four is 1,2,5,6
		light_ones = 7'b1001100; //four
		light_tens = 7'b0000001; //zero
		end
	5'b00101:				//5
		begin					//five is 0,2,3,5,6
		light_ones = 7'b0100100; //five
		light_tens = 7'b0000001; //zero
		end	5'b00110:				//6
		begin					//six is 0,2,3,4,5,6
		light_ones = 7'b0100000; //six
		light_tens = 7'b0000001; //zero
		end
	5'b00111:				//7
		begin					//seven is 0,1,2
		light_ones = 7'b0001111; //seven
		light_tens = 7'b0000001; //zero
		end
	5'b01000:				//8
		begin					//eight is 0,1,2,3,4,5,6
		light_ones = 7'b0000000; //eight
		light_tens = 7'b0000001; //zero
		end
	5'b01001:				//9
		begin					//nine is 0,1,2,5,6
		light_ones = 7'b0001100; //nine
		light_tens = 7'b0000001; //zero
		end
	5'b01010:				//10
		begin
		light_ones = 7'b0000001; //zero
		light_tens = 7'b1001111; //one
		end
	5'b01011:				//11
		begin
		light_ones = 7'b1001111; //one
		light_tens = 7'b1001111; //one
		end
	5'b01100:				//12
		begin
		light_ones = 7'b0010010; //two
		light_tens = 7'b1001111; //one
		end
	5'b01101:				//13
		begin
		light_ones = 7'b0000110; //three
		light_tens = 7'b1001111; //one
		end
	5'b01110:				//14
		begin
		light_ones = 7'b1001100; //four
		light_tens = 7'b1001111; //one
		end
	5'b01111:				//15
		begin
		light_ones = 7'b0100100; //five
		light_tens = 7'b1001111; //one
		end
	5'b10000:				//16
		begin
		light_ones = 7'b0100000; //six
		light_tens = 7'b1001111; //one
		end
	5'b10001:				//17
		begin
		light_ones = 7'b0001111; //seven
		light_tens = 7'b1001111; //one
		end
	5'b10010:				//18
		begin
		light_ones = 7'b0000000; //eight
		light_tens = 7'b1001111; //one
		end
	5'b10011:				//19
		begin
		light_ones = 7'b0001100; //nine
		light_tens = 7'b1001111; //one
		end
	5'b10100:				//20
		begin
		light_ones = 7'b0000001; //zero
		light_tens = 7'b0010010; //two
		end
	5'b10101:				//21
		begin
		light_ones = 7'b1001111; //one
		light_tens = 7'b0010010; //two
		end
	5'b10110:				//22
		begin
		light_ones = 7'b0010010; //two
		light_tens = 7'b0010010; //two
		end
	5'b10111:				//23
		begin
		light_ones = 7'b0000110; //three
		light_tens = 7'b0010010; //two
		end
	5'b11000:				//24
		begin
		light_ones = 7'b1001100; //four
		light_tens = 7'b0010010; //two
		end
	5'b11001:				//25
		begin
		light_ones = 7'b0100100; //five
		light_tens = 7'b0010010; //two
		end
	5'b11010:				//26
		begin
		light_ones = 7'b0100000; //six
		light_tens = 7'b0010010; //two
		end
	5'b11011:				//27
		begin
		light_ones = 7'b0001111; //seven
		light_tens = 7'b0010010; //two
		end
	5'b11100:				//28
		begin
		light_ones = 7'b0000000; //eight
		light_tens = 7'b0010010; //two
		end
	5'b11101:				//29
		begin
		light_ones = 7'b0001100; //nine
		light_tens = 7'b0010010; //two
		end
	5'b11110:				//30
		begin
		light_ones = 7'b0000001; //zero
		light_tens = 7'b0000110; //three
		end
	default:				// ??? something went wrong
		begin
		light_ones = 7'b1111111; //active low, ones should be off
		light_tens = 7'b1111111; //active low, tens should be off
		end



endcase


end

endmodule