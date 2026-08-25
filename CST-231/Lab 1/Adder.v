module Adder(
input [3:0] a,		//Input 1, 4 bits
input [3:0] b,		//input 2, 4 bits
output reg [4:0] c		//output, 5 bit register (since it needs to be changed and 2 four bit numbers can add up to a 5 bit number)
);

always @ (a or b) //when either of the inputs change, the output should change
begin

c = a + b; 			//the output is simply the sum of the inputs

end


endmodule