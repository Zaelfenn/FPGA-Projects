module Lab8(
input clk, //clock
input rst, //reset
input sen, //sensor
output [3:0] rgb1, //highway
output [3:0] rgb2, //farm
output led //clocksignal
);

assign rgb1[0] = 0;
assign rgb2[0] = 0;


ClkDivider u1 (clk, rst,led); //clock, reset, clockout

traffic_vsm u2 (led, sen, rst, rgb1[3:1], rgb2[3:1]); //clock, sensor, reset, highway, farm



endmodule