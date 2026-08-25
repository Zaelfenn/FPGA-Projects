module customIp(
	input [1:0] address,
	input chipselect,
	input clk, 
	input read,
	input reset_n,
	input write, 
	input [7:0] writedata,
	output reg [7:0] readdata,
	output [7:0] rgb_out
);

reg [7:0] DATA;

always@(posedge clk or negedge reset_n)
begin
if(~reset_n)
begin
	readdata <= 8'h0;
   DATA <= 8'h0;
end
else if (chipselect && write && (address == 2'b0) )
begin
	readdata <= 8'h0;
   case(writedata)
			8'h1: DATA <= 8'h1;
			8'h2: DATA <= 8'h2;
			8'h3: DATA <= 8'h4;
			8'h4: DATA <= 8'h5;
			8'h5: DATA <= 8'h3;
			8'h6: DATA <= 8'h6;
			8'h7: DATA <= 8'h7;
			default:  DATA <= 8'h0;
			endcase
end
else if (chipselect && read && (address == 2'b0))
begin
	readdata <= DATA;
	DATA <= DATA;
end
else
begin
	readdata <= readdata;
	DATA <= DATA;
end
 
end
assign rgb_out = DATA;
endmodule