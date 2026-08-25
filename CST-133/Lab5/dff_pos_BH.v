module dff_pos_BH( //d flip flop positive edge triggered behavioral
input d, //input d
input clk, //clock
output reg q //output q
);
always @(posedge clk) //anytime the clock is changing from 0 to 1
begin
q <= d; //q = d
end
endmodule