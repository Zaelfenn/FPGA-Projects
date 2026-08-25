module valid_code_check_sm(
input clk,				//1khz
input enable,
input [15:0] din,
output reg err,		//error light
output reg nerr		//success light
);

reg [3:0] state;
reg [12:0] counter; 			//5000 / 1000 = 5		means 13 bits
always @(posedge clk)
begin
if (counter > 5000)	
	begin
		state <= 4'b0001;		//reset state
		counter <= 13'b0;
	end
else if (enable)
	begin
		case (state)
			4'b0001:			//reset state
			begin
				state <= 4'b0010;
				counter <= 13'b0;
			end
			4'b0010:			//checking state
			begin
				counter <= 13'b0;
				case(din)
					16'h1234: state <= 4'b1000;
					16'habcd: state <= 4'b1000;
					16'h1122: state <= 4'b1000;
					16'h1010: state <= 4'b1000;
					16'h123a: state <= 4'b1000;
					16'h2580: state <= 4'b1000;		//non error state if correct code
					
					default: state <= 4'b0100;		//error state if not correct code
				endcase
			end
			4'b0100:			//error state
			begin
				state <= state;
				counter <= counter + 1;
			end
			4'b1000:			//no error state
			begin
				state <= state;
				counter <= counter + 1;
			end
			
			default:
			begin
				state <= 4'b0001;
				counter <= 13'b0;
			end
		endcase
	end

else
	begin
		counter <= 13'b0;
		state <= 4'b0001;
	end
end


always @(state)
begin

	case(state)
		4'b0001:			//reset state
		begin
			err <= 1'b0;
			nerr <= 1'b0;
		end
		4'b0010:			//checking state
		begin
			err <= 1'b0;
			nerr <= 1'b0;
		end
		4'b0100:			//error state
		begin
			err <= 1'b1;
			nerr <= 1'b0;
		end
		4'b1000:			//no error state
		begin
			err <= 1'b0;
			nerr <= 1'b1;
		end

	endcase
end




endmodule