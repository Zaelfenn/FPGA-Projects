module ClkDivider(
input clk,
input reset,
output reg clk_out
);
reg [24:0] count; // Make the counter big enough to hold our number
// Always block to handle the counter
always @(posedge clk or negedge reset)
begin
if(~reset)
count <= 25'b0;
else if(count < 25000000 - 1) // 50 MHz / (2 x 25 MHz) = 1 Hz
count <= count + 1;
else
count <= 25'b0;
end
// Always block to handle the flip flop portion
always @(posedge clk or negedge reset)
begin
if(~reset)
clk_out <= 1'b0;
else if(count == 25000000 - 1)
clk_out <= ~clk_out;
else
clk_out <= clk_out;
end
endmodule