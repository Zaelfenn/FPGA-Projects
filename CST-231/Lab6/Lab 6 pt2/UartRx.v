module UartRx(
input clk,				//16x as fast as transmitter
input rst, 
input din,				//each bit coming in
output reg [7:0] dout,	
output reg error,
output reg start			//enable the transmitter
);

parameter IDLE = 1, START = 2, RX = 4, PARITY = 8, DONE = 16, ERROR = 32;

reg [5:0] state;				//5 states
reg [3:0] counter; 			//count of 16 
reg [7:0] d_mod;				//data to modify
reg [3:0] rx_count;			//8 cycles
reg parity;						//parity bit
always @ (posedge clk or negedge rst)			//controls state
begin
if (~rst)
begin
	state <= IDLE;
end
else
	case(state)
			IDLE:						//wait for a 0
			begin
			
				if (~din)
				begin
					state <= START;
				end
				
				else
				begin
					state <= state;
				end
				
			end
			
			START:					//wait for a count of 16, then transition
			begin
				if (counter == 15)
				begin
					state <= RX;
				end
				
				else
				begin
					state <= state;
				end
			end

			RX:						//receiving every count of 8 modify a different bit of d_mod
			begin
				if (rx_count == 8) 
				begin
					state <= PARITY;
				end
				
				else
				begin
					state <= state;
				end
			end
			
			PARITY:					//check for parity, stay for a count of 8
			begin
				if (counter == 15)
				begin
					if (parity == d_mod[0] ^ d_mod[1] ^ d_mod[2] ^ d_mod[3] ^ d_mod[4] ^ d_mod[5] ^ d_mod[6] ^ d_mod[7])
						state <= DONE;
					else
						state <= ERROR;
				end
				
				else
				begin
					state <= state;
				end
			end
			
			DONE:						//parity was successful, go back to idle after a count of 8
			begin
				if (counter == 15)
				begin
					state <= IDLE;
				end
				
				else
				begin
					state <= state;
				end
			end
			
			ERROR:					//parity was unsuccessful, go back to idle after a count of 8
			begin
				if (counter == 15)
				begin
					state <= IDLE;
				end
				
				else
				begin
					state <= state;
				end
			end
			
			default:					//go to idle
			begin
				state <= IDLE;
			end
		
		endcase
end

always @ (posedge clk)			//controls internal workings
begin
case(state)
			IDLE:						//hold outputs, reset internal signals
			begin
				dout <= dout;
				error <= error;
				d_mod <= 8'h0;
				counter <= 4'h0;
				rx_count <= 4'h0;
				parity <= 1'h0;
				start <= 1'b0;				
			end
			
			START:					//hold outputs, hold internal signals, increment counter
			begin
				dout <= dout;
				error <= error;
				d_mod <= d_mod;
				counter <= counter + 1;
				rx_count <= rx_count;
				parity <= parity;
				start <= 1'b1;
			end

			RX:						//hold outputs, start internal signal changes
			begin 
				if (counter == 8)	//change d_mod halfway through
				begin
					dout <= dout;
					error <= error;
					rx_count <= rx_count;
					counter <= counter + 1;
					d_mod <= {din, d_mod[7:1]};		//shifts the data in bit by bit
					parity <= parity;
					start <= 1'b1;
				end
				
				else if (counter < 15) //increment counter and update parity
				begin
					dout <= dout;
					error <= error;
					rx_count <= rx_count;
					counter <= counter + 1;
					d_mod <= d_mod;
					parity <= d_mod[0] ^ d_mod[1] ^ d_mod[2] ^ d_mod[3] ^ d_mod[4] ^ d_mod[5] ^ d_mod[6] ^ d_mod[7];
					start <= 1'b1;
				end
				
				else						//increment rx_count, reset counter
				begin
					dout <= dout;
					error <= error;
					rx_count <= rx_count + 1;
					counter <= 4'h0;
					d_mod <= d_mod;
					parity <= parity;
					start <= 1'b1;
				end
			end
			
			PARITY:					//hold outputs, increment counter
			begin
				dout <= dout;
				error <= error;
				rx_count <= rx_count;
				counter <= counter + 1;
				d_mod <= d_mod;
				parity <= parity;
				start <= 1'b1;
			end
			
			DONE:						//output data, increment counter
			begin
				dout <= d_mod;
				error <= 1'b0;
				rx_count <= 4'h0;
				counter <= counter + 1;
				d_mod <= d_mod;
				parity <= parity;
				start <= 1'b1;
			end
			
			ERROR:					//output error, increment counter
			begin
				dout <= 8'h0;
				error <= 1'b1;
				rx_count <= 4'h0;
				counter <= counter + 1;
				d_mod <= d_mod;
				parity <= parity;
				start <= 1'b1;
			end
			
			default:
			begin
				dout <= 8'h0;
				error <= 1'b0;
				rx_count <= 4'h0;
				counter <= 4'h0;
				d_mod <= 8'h0;
				parity <= 1'b0;
				start <= 1'b1;
			end
		
		endcase

end

endmodule