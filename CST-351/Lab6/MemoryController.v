module MemoryController(
	input clk,
	input rst,
	input [6:0] input_data, //bit 6: car sensor, bits 5-3: highway light, bits 2-0: farm light
	output reg [5:0] address,
	output reg transmit
);

parameter IDLE = 1, RST_ASSERT = 2, CAR_DETECTED = 4, STATE_1 = 8, STATE_2 = 16, STATE_3 = 32, STATE_4 = 64, HOLD_MAX = 12, HOLD_MIN = 5;

reg rst_flag, car_flag;
reg [6:0] state, prev_state;  
reg [3:0] hold; //hold for 5-10 clock signals to give UART tx time to transmit
reg [4:0] counter; //27 characters in the longest line
always @ (posedge clk)
begin
	if (~rst)
	begin
		rst_flag <= 1'b1;
	end
	case(state)
	IDLE:
	begin
		prev_state <= prev_state;
		hold <= 0;
		counter <= 5'h1f;
		if(rst_flag == 1 && prev_state != RST_ASSERT)
		begin
			rst_flag <= 1'b0;
			state <= RST_ASSERT;
			car_flag <= car_flag;
		end
		else if (~rst)
		begin
			car_flag <= car_flag;
			state <= state;
		end
		else if (input_data[6] == 0 && ~car_flag && prev_state != CAR_DETECTED)
		begin
			car_flag <= 1'b1;
			state <= CAR_DETECTED;
		end
		else
		begin
			case({input_data[4:3],input_data[1:0]})
			4'b1001:  // farm red, highway green
				if(prev_state != STATE_1)
				begin
					rst_flag <= 1'b0;
					car_flag <= car_flag;
					state <= STATE_1;
				end
				else
				begin
					rst_flag <= 1'b0;
					car_flag <= car_flag;
					state <= IDLE;
				end
			4'b1101: //farm red, highway yellow
				if(prev_state != STATE_2)
				begin
					car_flag <= car_flag;
					state <= STATE_2;
				end
				else
				begin
					car_flag <= car_flag;
					state <= IDLE;
				end
			4'b0110: //farm green, highway red
				if(prev_state != STATE_3)
				begin
					car_flag <= car_flag;
					state <= STATE_3;
				end
				else
				begin
					car_flag <= car_flag;
					state <= IDLE;
				end
			4'b0111: //farm yellow, highway red
				if(prev_state != STATE_4)
				begin
					state <= STATE_4;
					car_flag <= 1'b0;
				end
				else
				begin
					state <= IDLE;
					car_flag <= 1'b0;
				end
			default:
			begin
				car_flag <= car_flag;
				state <= IDLE;
			end
			endcase
		end
	end
	RST_ASSERT: //23 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 23)
			begin
				prev_state <= RST_ASSERT;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= RST_ASSERT;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end
	CAR_DETECTED: //21 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 21)
			begin
				prev_state <= CAR_DETECTED;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= CAR_DETECTED;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end
		
	STATE_1: //27 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 27)
			begin
				prev_state <= STATE_1;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= STATE_1;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end
		
	STATE_2: //28 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 28)
			begin
				prev_state <= STATE_2;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= STATE_2;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end
		
	STATE_3: //27 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 27)
			begin
				prev_state <= STATE_3;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= STATE_3;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end
		
	STATE_4: //28 characters
		begin
			if(hold == HOLD_MIN)
			begin
				prev_state <= prev_state;
				counter <= counter + 1;
				state <= state;
				hold <= hold + 1;
			end
			else if (hold >= HOLD_MAX)
			begin
				prev_state <= prev_state;
				counter <= counter;
				hold <= 0;
				state <= state;
			end
			else if (counter != 28)
			begin
				prev_state <= STATE_4;
				hold = hold + 1;
				counter <= counter;
				state <= state;
			end
			else
			begin
				prev_state <= STATE_4;
				hold <= 0;
				counter <= 5'h1f;
				state <= IDLE;
			end
		end

	default: 
	begin
		prev_state <= IDLE;
		hold <= 0;
		counter <= 5'h1f;
		state <= IDLE;
	end
	endcase

end

always @ (posedge clk)
begin
	case(state)
	
		IDLE: 
		begin
			address <= 6'h0;
			transmit <= 1'b1;
		end
		
		RST_ASSERT: //INPUT: Reset Asserted\n
		begin
		case(counter)
				0: 
				begin
					address <= 6'h3; //"I"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h4; //"N"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h5; //"P"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h6; //"U"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				7: 
				begin
					address <= 6'h10; //"R"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'h11; //"s"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'hD; //"t"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'h12; //"A"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'h11; //"s"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'h11; //"s"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				16: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'hA; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'hD; //"t"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20: 
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				21: 
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				22:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end
		
		CAR_DETECTED: //INPUT: Car Detected\n
		begin
		case(counter)
				0: 
				begin
					address <= 6'h3; //"I"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h4; //"N"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h5; //"P"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h6; //"U"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				
				7: 
				begin
					address <= 6'h8; //"C"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'h9; //"a"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'hA; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'hB; //"D"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'hD; //"t"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'hE; //"c"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end	
				
				16: 
				begin
					address <= 6'hD; //"t"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end
		
		STATE_1: //STATE: Farm Red, HW Green\n
		begin
			case(counter)
				0: 
				begin
					address <= 6'h13; //"S"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h12; //"A"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h14; //"E"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				7: 
				begin
					address <= 6'h15; //"F"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'h9; //"a"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'ha; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'h16; //"m"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'h10; //"R"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'h17; //","
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				16: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'h18; //"H"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'h19; //"W"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20: 
				begin
					address <= 6'h1A; //"G"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				21: 
				begin
					address <= 6'hA; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				22:
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				23:
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				24:
				begin
					address <= 6'h1B; //"n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				25:
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				26:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end	
		
		STATE_2: //STATE: Farm Red, HW Yellow
		begin
			case(counter)
				0: 
				begin
					address <= 6'h13; //"S"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h12; //"A"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h14; //"E"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				7: 
				begin
					address <= 6'h15; //"F"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'h9; //"a"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'ha; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'h16; //"m"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'h10; //"R"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'h17; //","
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				16: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'h18; //"H"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'h19; //"W"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20: 
				begin
					address <= 6'h1C; //"Y"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				21: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				22:
				begin
					address <= 6'h1D; //"l"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				23:
				begin
					address <= 6'h1D; //"l"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				24:
				begin
					address <= 6'h1E; //"o"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				25:
				begin
					address <= 6'h1F; //"w"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				26:
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				27:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end
		
		STATE_3: //STATE: Farm Green, HW Red
		begin
			case(counter)
				0: 
				begin
					address <= 6'h13; //"S"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h12; //"A"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h14; //"E"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				7: 
				begin
					address <= 6'h15; //"F"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'h9; //"a"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'ha; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'h16; //"m"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'h1; //" "
					transmit <= ( HOLD_MAX > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'h1A; //"G"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'hA; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				16: 
				begin
					address <= 6'h1B; //"n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'h17; //","
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'h18; //"H"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20: 
				begin
					address <= 6'h19; //"W"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				21: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				22:
				begin
					address <= 6'h10; //"R"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				23:
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				24:
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				25:
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				26:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end
		
		STATE_4: //STATE: Farm Yellow, HW Red
		begin
			case(counter)
				0: 
				begin
					address <= 6'h13; //"S"
					transmit <= (HOLD_MIN < hold) ? 1'b1 : 1'b0;
				end
				
				1: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				2: 
				begin
					address <= 6'h12; //"A"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				3: 
				begin
					address <= 6'h7; //"T"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				4: 
				begin
					address <= 6'h14; //"E"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				5: 
				begin
					address <= 6'h2; //":"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				6: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				7: 
				begin
					address <= 6'h15; //"F"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				8: 
				begin
					address <= 6'h9; //"a"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				9: 
				begin
					address <= 6'ha; //"r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				10: 
				begin
					address <= 6'h16; //"m"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				11: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				12: 
				begin
					address <= 6'h1C; //"Y"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				13: 
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				14: 
				begin
					address <= 6'h1D; //"l"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				15: 
				begin
					address <= 6'h1D; //"l"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				16: 
				begin
					address <= 6'h1E; //"o"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				17: 
				begin
					address <= 6'h1F; //"w"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				18: 
				begin
					address <= 6'h17; //","
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				19: 
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				20: 
				begin
					address <= 6'h18; //"H"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				21: 
				begin
					address <= 6'h19; //"W"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				22:
				begin
					address <= 6'h1; //" "
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				23:
				begin
					address <= 6'h10; //"R"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				24:
				begin
					address <= 6'hC; //"e"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				25:
				begin
					address <= 6'hF; //"d"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				26:
				begin
					address <= 6'h0; //"\n"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				27:
				begin
					address <= 6'h20; //"\r"
					transmit <= (HOLD_MIN > hold) ? 1'b1 : 1'b0;
				end
				
				default:
				begin
					address <= 6'h0; //"\n"
					transmit <= 1'b1;
				end
			endcase
		end

		default:
		begin
			address <= 6'h1f;
			transmit <= 1'b1;
		end
		
	endcase
end
endmodule