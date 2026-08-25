module LightController(
input clk,
input rst,
input left,
input right, 
input brake,
input haz,
output reg [2:0] R_LIGHTS,
output reg [2:0] L_LIGHTS
);

reg [6:0] state;									//6 states
reg h_bit;											//controls hazard output
reg [1:0] t_bit;									//controls turning outputs
parameter IDLE = 1, T_R = 2, T_L = 4, T_R_B = 8, T_L_B = 16, BRAKE = 32, HAZARD = 64;

always @ (posedge clk or negedge rst)
begin
if (~rst)
begin
	state <= IDLE;
end
else
	case (state)
		IDLE:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (left & brake)
			begin
				state <= T_L_B;
				t_bit <= 2'b0;
			end
			else if (right & brake)
			begin
				state <= T_R_B;
				t_bit <= 2'b0;
			end
			else if (left)
			begin
				state <= T_L;
				t_bit <= 2'b0;
			end
			else if (right)
			begin
				state <= T_R;
				t_bit <= 2'b0;
			end
			else if (brake)
			begin
				state <= BRAKE;
			end
			else 
			begin
				state <= state;
			end
		end
		
		T_R:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (right & brake)
			begin
				state <= T_R_B;
				t_bit <= t_bit + 1;
			end
			else if (~right)
			begin
				state <= IDLE;
			end
			else
			begin
				state <= state;
				t_bit <= t_bit + 1;
			end
		end
		
		T_L:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (left & brake)
			begin
				state <= T_L_B;
				t_bit <= t_bit + 1;
			end
			else if (~left)
			begin
				state <= IDLE;
			end
			else
			begin
				state <= state;
				t_bit <= t_bit + 1;
			end
		end
		
		T_R_B:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (~brake & right)
			begin
				state <= T_R;
				t_bit <= t_bit + 1;
			end
				
			else if (~right)
			begin
				state <= BRAKE;
			end
			else if (~brake & ~right)
			begin
				state <= IDLE;
			end
			else
			begin
				state <= state;
				t_bit <= t_bit + 1;
			end
		end
		
		T_L_B:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (~brake & left)
			begin
				state <= T_L;
				t_bit <= t_bit + 1;
			end
			else if (~left)
			begin
				state <= BRAKE;
			end
			else if (~brake & ~left)
			begin
				state <= IDLE;
			end
			else
			begin
				state <= state;
				t_bit <= t_bit + 1;
			end

		end
		
		BRAKE:
		begin
			if (haz)
			begin
				state <= HAZARD;
				h_bit <= 1'b0;
			end
			else if (left & brake)
			begin
				state <= T_L_B;
				t_bit <= 2'b0;
			end
			else if (right & brake)
			begin
				state <= T_R_B;
				t_bit <= 2'b0;
			end
			else if (~brake)
			begin
				state <= IDLE;
			end
			else
			begin
				state <= state;
			end
		end
		
		HAZARD:
		begin
			if (haz)
			begin
				state <= state;
				h_bit <= ~h_bit;
			end
			else
			begin
				state <= IDLE;
			end
		end
		
		default:
		begin
			state <= IDLE;
		end
		

endcase

end


always @(posedge clk or negedge rst)
begin
case (state)
	IDLE:			//all lights off
	begin
		R_LIGHTS <= 3'h0;
		L_LIGHTS <= 3'h0;
	end
	
	T_R:			//left lights off, right goes 0-1-3-7-0
	begin
		case (t_bit)
			2'h0:
			begin
				R_LIGHTS <= 3'h1;
				L_LIGHTS <= 3'h0;
			end
			
			2'h1: 
			begin
				R_LIGHTS <= 3'h3;
				L_LIGHTS <= 3'h0;
			end
			
			2'h2:
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h0;
			end
			
			2'h3:	
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
			
			default:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
		endcase
	end
	
	T_L:			//left light goes 0-1-3-7-0, right off
	begin
		
		
		case (t_bit)
			2'h0:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h1;
			end
			
			2'h1: 
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h3;
			end
			
			2'h2:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h7;
			end
			
			2'h3:	
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
			
			default:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
		endcase
	end
	
	T_R_B:		//left lights 7, right goes 0-1-3-7-0
	begin
		case (t_bit)
			2'h0:
			begin
				R_LIGHTS <= 3'h1;
				L_LIGHTS <= 3'h7;
			end
			
			2'h1: 
			begin
				R_LIGHTS <= 3'h3;
				L_LIGHTS <= 3'h7;
			end
			
			2'h2:
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h7;
			end
			
			2'h3:	
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h7;
			end
			
			default:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
		endcase
	end
	
	T_L_B:		//left lights go 0-1-3-7-0, right 7
	begin
		case (t_bit)
			2'h0:
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h1;
			end
			
			2'h1: 
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h3;
			end
			
			2'h2:
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h7;
			end
			
			2'h3:	
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h0;
			end
			
			default:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
				t_bit <= 1'b0;
			end
		endcase
	end
	
	BRAKE:		//all lights 7
	begin
		R_LIGHTS <= 3'h7;
		L_LIGHTS <= 3'h7;
	end
	
	HAZARD:		//all lights go 7-0-7
	begin
		case (h_bit)
			1'b0:
			begin
				R_LIGHTS <= 3'h7;
				L_LIGHTS <= 3'h7;
			end
			
			1'b1:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
			
			default:
			begin
				R_LIGHTS <= 3'h0;
				L_LIGHTS <= 3'h0;
			end
		
		endcase
		
	end
	
	default:
	begin
		R_LIGHTS <= 3'h0;
		L_LIGHTS <= 3'h0;
	end
	
	endcase

end

endmodule
