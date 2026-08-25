module TopLevel(
input [3:0] first, 				//first input
input [3:0] second, 				//second input
output [6:0] fir_one,			//ones place (in decimal) of first input
output [6:0] fir_ten,			//tens place (in decimal) of first input
output [6:0] sec_one,			//ones place (in decimal) of second input
output [6:0] sec_ten,			//tens place (in decimal) of second input
output [6:0] sum_one,			//ones place (in decimal) of the sum of the inputs
output [6:0] sum_ten				//tens place (in decimal) of the sum of the inputs
);
/////////////////////
// WIRE DECLARATION //
/////////////////////

wire [4:0] sum; //holds sum of first and second

//////////////////////////
// WIRE DECLARATION DONE //
//////////////////////////

Adder u1 (first, second, sum); //adds inputs and stores in sum

SevenSegDec u2 ({1'b0,first}, fir_one, fir_ten); //puts first input through decoder, display on middle seven seg

SevenSegDec u3 ({1'b0,second}, sec_one, sec_ten); //puts second input through decoder, display on left most seven seg

SevenSegDec u4 (sum, sum_one, sum_ten); //puts the sum of first and second through decoder, display on right most seven seg


endmodule