module dff_neg_BH( //d flip flop negative edge triggered behavioral
input d, //input d
input clk, //input clock
output reg q //output
);
always @(negedge clk) //anytime the clock is changing from 1 to 0
begin
q <= d; //q = d
end
endmodule