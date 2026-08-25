module ButtonCheck(
input clk,
input rst,
input nenable, 				//enable on low (busy flag)
input press,					//active low
input [7:0] din,
output reg [7:0] dout,		//character out
output reg ena					//
);


reg [2:0] state;		//3 states- enable + no press, enable + press, not enable
parameter press_wait = 1, press_found = 2, done_wait = 4; 

always @ (posedge clk)
begin
if (~rst)
begin
	state <= press_wait;		//reset to waiting state
end
else
	case (state)
	press_wait:
	begin
		if (nenable)
			state <= state;
		else if (~press)
			state <= press_found;
		else
			state <= state;
	end
	
	press_found:
	begin
		if (~press)
			state <= done_wait;
		else
			state <= press_wait;
	end
	
	done_wait:
	begin
		if (nenable)
			state <= state;
		else if (press)
			state <= press_wait;
		else
			state <= state;
	end
	
	default:
	begin
		state <= press_wait;
	end
	
	endcase
end

always @ (state)
begin

case (state)
	press_wait:		//enabled but no press
	begin
		dout <= din;
		ena <= 1'b1;	//active low button
	end
	
	press_found:
	begin
		dout <= din;
		ena <= 1'b0;
	end
	
	done_wait:
	begin
		dout <= din;
		ena <= 1'b1;
	end
	
	default:
	begin
		dout <= din;
		ena <= 1'b1;
	end
	
	endcase

end

endmodule