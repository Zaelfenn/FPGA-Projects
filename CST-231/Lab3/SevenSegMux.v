module SevenSegMux(
input [1:0] sel,						//select bit
input [6:0] a,							//highest digit (4)
input [6:0] b,							//second highest digit (3) 
input [6:0] c,							//second lowest digit (2) 
input [6:0] d,							//lowest digit (1)
output reg [6:0] mout						//mux output
);

always @(sel or a or b or c or d)		//whenever the select bit changes, output should change
begin
	case(sel)
		2'b00: mout <= a;				//digit 4
		2'b01: mout <= b;				//digit 3
		2'b10: mout <= c;				//digit 2
		2'b11: mout <= d;				//digit 1
		default: mout <= 7'bzzzzzzz;
	endcase
end
endmodule