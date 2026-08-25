module decideInput(
	input keyIn,
	input textIn,
	input [9:0] data_in,
	output reg [9:0]key_in,
	output reg [7:0]text_in
);

reg [9:0]key;
reg [7:0]text;

always@(keyIn or textIn)
begin
	if(!keyIn)
		begin
			key_in <= data_in;
			key <= data_in;
			text_in <= text;
		end
	else if(!textIn)
		begin
			key_in <= key;
			text_in <= data_in[7:0];
			text <= data_in[7:0];
		end
	else
		begin
			key_in <= key;
			text_in <= text;
		end
end

endmodule