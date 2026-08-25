module UartTx(
input clk,
input rst, 
input [7:0] din,
input start,
output reg dout,
output reg busy
);


reg [4:0] state; 					//5 states
parameter idle = 1, start_s = 2, transmit = 4, parity = 8, done = 16;
reg [7:0] data;
reg [3:0] counter;
always @(posedge clk)
begin
if (~rst)
begin
state <= idle;
data <= 8'h0;
counter <= 4'h7;
end
else
	case (state)
	idle:
	begin
		if (start)				//active low signal
		begin
			state <= state;
			data <= 8'h0;
			counter <= 4'h7;
		end
		else
		begin
			state <= start_s;	
			data <= din;
			counter <= 4'h7;
		end
	end
	
	start_s:
	begin
		state <= transmit;
		data <= data;
		counter <= 4'h7;
	end
	
	transmit:
	begin
		if (counter > 0)
			begin
				state <= state;
				data <= {data[0], data[7:1]};
				counter <= counter - 1;
			end
		else
			begin
				state <= parity;
				data <= data;
				counter <= counter;
			end
	end
	
	parity:
	begin
		state <= done;
		data <= data;
		counter <= counter;
	end
	
	done:
	begin
		if (start)				//button released
			begin
			state <= idle;
			counter <= counter;
			data <= data;
			end
		else
			begin
			state <= state;
			counter <= counter;
			data <= data;
			end
	end
	
	default:
	begin
		state <= idle;
		counter <= 4'h8;
		data <= 8'h0;
	end
	
	endcase

end

always @(state or data)
begin
	case (state)
	idle:
	begin
		dout <= 1'b1;
		busy <= 1'b0;
	end
	
	start_s:
	begin
		dout <= 1'b0;
		busy <= 1'b1;
	end
	
	transmit:
	begin
		dout <= data[0];
		busy <= 1'b1;
	end
	
	parity:
	begin
		dout <= (data[0] ^ data[1] ^ data[2] ^ data[3] ^ data[4] ^ data[5] ^ data[6] ^ data[7]);
		busy <= 1'b1;
	end
	
	done:
	begin
		dout <= 1'b1;
		busy <= 1'b0;
	end
	
	default:
	begin
		dout <= 1'b1;
		busy <= 1'b1;
	end
	
	endcase


end

endmodule