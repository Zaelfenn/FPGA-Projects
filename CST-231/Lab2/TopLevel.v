module TopLevel(
input clk,
input rst,
input ena, 
output [34:0] lights
);
wire clk_out;
wire [15:0] count_out;
wire [19:0] bcd_out;

ClkDivider #(50000,16) u1 (clk, rst, ena, clk_out); 		//inputs: clock, reset, enable 		outputs: clock_out

Counter u2 (clk_out, rst, ena, count_out);							//inputs: clock, reset, enable				outputs: count

BCDDec u3 (count_out, bcd_out);								//inputs: binary_in				outputs: bcd_out

SevenSegDecoder d1 (bcd_out[3:0], lights[6:0]);				//digit 1		inputs: data_in			outputs: lights[6:0]
SevenSegDecoder d2 (bcd_out[7:4], lights[13:7]);				//digit 2		inputs: data_in			outputs: lights[13:7]
SevenSegDecoder d3 (bcd_out[11:8], lights[20:14]);				//digit 3		inputs: data_in			outputs: lights[20:14]
SevenSegDecoder d4 (bcd_out[15:12], lights[27:21]);				//digit 4		inputs: data_in			outputs: lights[27:21]
SevenSegDecoder d5 (bcd_out[19:16], lights[34:28]);				//digit 5		inputs: data_in			outputs: lights[34:28]

endmodule