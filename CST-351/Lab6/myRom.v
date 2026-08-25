module myRom(
	input clk,
	input [5:0] char_address,
	output reg [7:0] char_out
);


/***************************************************************
* Phrases to output
*---------------------
*
* 1. INPUT: Car Detected
* 2. INPUT: Reset Asserted
* 3. STATE: Farm Red, HW Green //state 1
* 4. STATE: Farm Red, HW Yellow //state 2
* 5. STATE: Farm Green, HW Red //state 3
* 6. STATE: Farm Yellow, HW Red //state 4
*
***************************************************************/
reg [7:0] int_memory [32:0]; //32 unique characters
always @ (posedge clk)
begin
	int_memory[0] = 8'h0A; //line feed
	int_memory[1] = 8'h20; //space
	int_memory[2] = 8'h3A; //colon
	int_memory[3] = 8'h49; //"I"
	int_memory[4] = 8'h4E; //"N"
	int_memory[5] = 8'h50; //"P"
	int_memory[6] = 8'h55; //"U"
	int_memory[7] = 8'h54; //"T"
	int_memory[8] = 8'h43; //"C"
	int_memory[9] = 8'h61; //"a"
	int_memory[10] = 8'h72; //"r"
	int_memory[11] = 8'h44; //"D"
	int_memory[12] = 8'h65; //"e"
	int_memory[13] = 8'h74; //"t"
	int_memory[14] = 8'h63; //"c"
	int_memory[15] = 8'h64; //"d"
	int_memory[16] = 8'h52; //"R"
	int_memory[17] = 8'h73; //"s"
	int_memory[18] = 8'h41; //"A"
	int_memory[19] = 8'h53; //"S"
	int_memory[20] = 8'h45; //"E"
	int_memory[21] = 8'h46; //"F"
	int_memory[22] = 8'h6D; //"m"
	int_memory[23] = 8'h2C; //comma
	int_memory[24] = 8'h48; //"H"
	int_memory[25] = 8'h57; //"W"
	int_memory[26] = 8'h47; //"G"
	int_memory[27] = 8'h6E; //"n"
	int_memory[28] = 8'h59; //"Y"
	int_memory[29] = 8'h6C; //"l"
	int_memory[30] = 8'h6F; //"o"
	int_memory[31] = 8'h77; //"w"
	int_memory[32] = 8'h0D; //carriage return
	
	char_out = int_memory[char_address];
end
endmodule