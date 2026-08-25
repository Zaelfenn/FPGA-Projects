module dlatch_BH( //d latch behavioral
input d, //input d
input clk, //clock
output reg q //output
);
always @(*) //anytime an input changes
begin
if(clk) //if the clock is high
q <= d; //q = d
end
endmodule