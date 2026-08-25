module DigClock(
input clk,
input rst, 
input set,
input mins,
input hrs,
output reg [3:0] sec_ones,
output reg [2:0] sec_tens,
output reg [3:0] min_ones,
output reg [2:0] min_tens,
output reg [3:0] hour_ones,
output reg  hour_tens,
output reg am_pm
);

reg [2:0] state;
parameter RESET = 1, IDLE = 2, SET = 4;

always @(posedge clk)
begin
if (~rst)
begin
	state <= RESET;
end
else
begin
	case (state)
	
	RESET:
	begin
		state <= IDLE;
	end
	
	IDLE:
	begin
		if (set)
		begin
			state <= SET;
		end
		
		else
		begin
			state <= state;
		end
	end
	
	SET:
	begin
		if (~set)
		begin
			state <= IDLE;
		end
		
		else
		begin
			state <= state;
		end
	end
	
	default:
	begin
		state <= IDLE;
	end
	
	endcase
	
	
end
end



always @ (posedge clk)
begin
	case (state)
	
	RESET:
	begin
		sec_ones <= 4'h0;
		sec_tens <= 3'h0;
		min_ones <= 4'h0;
		min_tens <= 3'h0;
		hour_ones <= 4'h2;
		hour_tens <= 1'b1;
		am_pm <= 1'b0;
	end
	
	IDLE:
	begin
		sec_ones <= sec_ones + 1;
		if (sec_ones == 9)
		begin
			sec_ones <= 4'h0;
			sec_tens <= sec_tens + 1;
			
			if (sec_tens == 5 && sec_ones == 9)
			begin
				sec_tens <= 3'h0;
				min_ones <= min_ones + 1;
				if (min_ones == 9)
				begin
					min_ones <= 4'h0;
					min_tens <= min_tens + 1;
					if (min_tens == 5 && min_ones == 9)
					begin
						min_tens <= 3'h0;
						hour_ones <= hour_ones + 1;
						if (hour_ones == 9)
						begin
							hour_tens <= hour_tens + 1;
						end
						
						
						if (hour_tens == 1 && hour_ones == 1 && sec_tens == 5 && sec_ones == 9 && min_ones == 9 && min_tens == 5)
							begin
								am_pm <= ~am_pm;
							end
							else if (hour_tens == 1 && hour_ones == 2 && sec_tens == 5 && sec_ones == 9 && min_ones == 9 && min_tens == 5)
							begin
								hour_ones <= 4'h1;
								hour_tens <= 4'h0;
							end
					end
				end
			end
		end
	end
	
	SET:
	begin
		if (mins)
		begin
			min_ones <= min_ones + 1;
			if (min_ones == 9)
				begin
					min_ones <= 4'h0;
					min_tens <= min_tens + 1;
					if (min_tens == 6)
					begin
						min_tens <= 3'h0;
					end
				end
		end
		
		else if (hrs)
		begin
			hour_ones <= hour_ones + 1;
			if (hour_ones == 9)
			begin
				hour_ones <= 4'h0;
				hour_tens <= hour_tens + 1;				
			end
			if (hour_tens == 1 && hour_ones == 1)
			begin
				am_pm <= ~am_pm;
			end
			else if (hour_tens == 1 && hour_ones == 2)
			begin
				hour_ones <= 4'h1;
				hour_tens <= 4'h0;
			end
		end
	end
	
	default:
	begin
		sec_ones <= 4'h0;
		sec_tens <= 3'h0;
		min_ones <= 4'h0;
		min_tens <= 3'h0;
		hour_ones <= 4'h2;
		hour_tens <= 1'b1;
		am_pm <= 1'b0;
	end
	
	endcase


end


endmodule