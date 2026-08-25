module topLevel(
	input [3:0] data_in,
	output [6:0] data_out
);

SevenSegDecoder d1 (data_in, data_out);

endmodule
