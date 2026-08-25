module TopLevel(
input clk,			//internal 50MHz clock
input rst, 			//sw_0
input set,			//key_0
input mins, 		//key_1
input hrs, 			//key_2
output [41:0] clock,		//hex0 - hex6
output am_pm		//LED 0
);

wire c_set, c_min, c_hrs, c_clk;

wire [6:0] seconds;
wire [6:0] minutes;
wire [4:0] hours;

not u1(c_set, set);
not u2(c_min, mins);
not u3(c_hrs, hrs);

ClkDivider			#(25000000, 26)			c1(clk, rst, 1'b0, c_clk);

DigClock							c2(c_clk, rst, c_set, c_min, c_hrs, seconds[3:0], seconds [6:4], minutes[3:0], minutes[6:4], hours[3:0], hours[4], am_pm);

SevenSegDecoder				sec1(seconds[3:0], clock[6:0]);
SevenSegDecoder				sec2(seconds[6:4], clock[13:7]);
SevenSegDecoder				min1(minutes[3:0], clock[20:14]);
SevenSegDecoder				min2( minutes[6:4], clock[27:21]);
SevenSegDecoder				hour1(hours[3:0], clock[34:28]);
SevenSegDecoder				hour2(hours[4], clock[41:35]);


endmodule