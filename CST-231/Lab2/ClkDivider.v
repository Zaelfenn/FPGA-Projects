module ClkDivider 
					#(parameter DIVIDER = 12500000,
									BITS = 25)				//default 1 second clock
					 (input clk,										//system clock input, 50MHz
					  input rst, 										//active low reset
					  input ena, 										//active low enable
					  output reg clk_out);							//clock out signal

	reg [BITS-1:0] count;													//variable bit counter can divide clock as needed, default up to approx. one second
			
			
always @ (negedge clk)
begin
	if (~rst)
	begin
		clk_out <= 1'b0;										//if resetting, keep clock output low
		count = 0;
	end
	else if (ena)
		begin	//if enable isn't active, hold the value
			clk_out <= clk_out;
			count <= count;
		end
	else if (count < DIVIDER)								//if the count has not yet hit the parameter for division, add one to it
	begin
		count <= count + 1;
		clk_out <= clk_out;
	end
	else
	begin
		clk_out <= ~clk_out;									//otherwise, invert the output
		count <= 0;
	end
end
					  
					  

endmodule