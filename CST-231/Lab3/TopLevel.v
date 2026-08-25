module TopLevel(input clk,
input ena, 
input u_d,
input rst,
output [11:0] digit_out
);
wire clk_out, clk_mux;
wire [11:0] counter_out;
wire [15:0] bcd_out;
wire [27:0] digits;
wire [6:0] mux_out;
wire [1:0] sel_mux;

ClkDivider 			u1 (clk, rst, ena, clk_out);											//used for SevenSeg Display bits
Counter				u3 (clk_out, rst, ena, u_d, counter_out);							//used for SevenSeg Display bits
BCDDec				u5 (counter_out, bcd_out);												//used for sevenseg display

ClkDivider		#(10000, 14) u6 (clk, 1'b1, 1'b0, clk_mux);							//used for mux/demux, mux should display all 4 digits regardless of if it is paused or not
Counter			#(2)			 u7 (clk_mux, 1'b1, 1'b0, 1'b1, sel_mux);				//used for mux/demux

SevenSegDecoder		d1 (bcd_out[15:12], digits[27:21]);							//digit 1
SevenSegDecoder		d2	(bcd_out[11:8], digits[20:14]);							//digit 2
SevenSegDecoder		d3	(bcd_out[7:4], digits[13:7]);								//digit 3
SevenSegDecoder		d4	(bcd_out[4:0], digits[6:0]);								//digit 4

SevenSegMux				m1 (sel_mux, digits[27:21], digits[20:14], digits[13:7], digits[6:0], mux_out);
SevenSegDeMux			m2	(sel_mux, mux_out, digit_out);


endmodule