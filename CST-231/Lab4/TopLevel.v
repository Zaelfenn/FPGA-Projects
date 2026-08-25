module TopLevel(
input clk,
input ena,
input rst, 
input [3:0] cols,
output [3:0] rows, 
output [27:0] seven_segment,			//7 segments * 4 = 28 bits
output [1:0] led_out					//2 led's to turn on = 2 bits , led_out[0] = error, led_out[1] = no error
);

wire thousand_hertz, keypad_ena, shift_ena, shift_rst, val_rst, val_ena;
wire [3:0] keypad_out;
wire [15:0] shift_out;


ClkDivider		#(12500, 14)		u1 (clk, rst, ena, thousand_hertz);				//1KHz

keypad_check_sm 						sm1 (thousand_hertz, rst, cols, rows, keypad_out, keypad_ena);
shift_in_sm								sm2 (thousand_hertz, keypad_ena, keypad_out, shift_rst, shift_out, shift_ena);
valid_code_check_sm					sm3 (thousand_hertz, shift_ena, shift_out, led_out[0], led_out[1]);

SevenSegDecoder						ss1 (shift_out[3:0], seven_segment[6:0]);
SevenSegDecoder						ss2 (shift_out[7:4], seven_segment[13:7]);
SevenSegDecoder						ss3 (shift_out[11:8], seven_segment[20:14]);
SevenSegDecoder						ss4 (shift_out[15:12], seven_segment[27:21]);


endmodule