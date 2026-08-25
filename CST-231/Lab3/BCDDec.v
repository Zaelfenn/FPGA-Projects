module BCDDec(
   input [11:0] bin,									//max value is 4096
   output reg [15:0] bcd							//4096 is 4 digits, 4 * 4 is 20, therefore 16 bit register output
   );
   
integer i;
	
always @(bin) begin
    bcd=0;		 	
    for (i=0;i<11;i=i+1) begin											//Iterate once for each bit in input number
			if (bcd[3:0] >= 5) 
				bcd[3:0] = bcd[3:0] + 3;				//If any BCD digit is >= 5, add three
			
			if (bcd[7:4] >= 5) 
				bcd[7:4] = bcd[7:4] + 3;
			
			if (bcd[11:8] >= 5) 
				bcd[11:8] = bcd[11:8] + 3;
	
			bcd = {bcd[14:0],bin[11-i]};									//Shift one bit, and shift in proper bit from input 
    end
end
endmodule
