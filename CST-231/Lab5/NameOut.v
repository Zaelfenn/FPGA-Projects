module NameOut(
input clk,
input rst,
input ena,			//button press detected (active low)
output reg [7:0] char
);
//output: Hello Zael ^w^
//////ascii values////////
//			H- 0x48			//
//			e- 0x65			//
//			l- 0x6c			//
//			o- 0x6f			//
//			 - 0x20			//
//			Z- 0x5A			//
//			a- 0x61			//
//			^-	0x5e			//
//			w- 0x77			//
//////////////////////////

//14 characters, 15 states

reg [14:0] state; 



always @ (posedge clk)
begin
if (~rst)
begin
	state <= 4'h0;
end
else 			
	case (state)		//change output based on state
		15'h1:
		begin
			if (~ena)
			begin
				state <= 15'h2;
			end
			
			else
			begin
				state <= state;
			end
		end
		15'h2:					//output- H
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h4;
		end
		end
		
		15'h4:					//output- e
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h8;
		end
		end
		
		15'h8:					//output- l
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h10;
		end
		end
		
		15'h10:					//output- l
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h20;
		end
		end
		
		15'h20:					//output- o
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h40;
		end
		end
		
		15'h40:					//output- space
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h80;
		end
		end
		
		15'h80:					//output- Z
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h100;
		end
		end
		
		15'h100:					//output- a
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h200;
		end
		end
		
		15'h200:					//output- e
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h400;
		end
		end
		
		15'h400:					//output- l
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h800;
		end
		end
		
		15'h800:					//output- space
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h1000;
		end
		end
		
		15'h1000:					//output- ^
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h2000;
		end
		end
		
		15'h2000:					//output- w
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h4000;
		end
		end
		
		15'h4000:					//output- ^
		begin
		if (ena)
		begin
			state <= state;
		end
		else
		begin
			state <= 15'h1;
		end
		end
		
		
		
		default:
		begin
			state <= 15'h1;
		end
		endcase
end


always @ (state)
begin

	case (state)		//change output based on state
		15'h1:					//output nothing
		begin
			char <= 8'h20;
		end
		15'h2:					//output- H
		begin
			char <= 8'h48;
		end
		
		15'h4:					//output- e
		begin
			char <= 8'h65;
		end
		
		15'h8:					//output- l
		begin
			char <= 8'h6c;
		end
		
		15'h10:					//output- l
		begin
			char <= 8'h6c;
		end
		
		15'h20:					//output- o
		begin
			char <= 8'h6f;
		end
		
		15'h40:					//output- space
		begin
			char <= 8'h20;
		end
		
		15'h80:					//output- Z
		begin
			char <= 8'h5a;
		end
		
		15'h100:					//output- a
		begin
			char <= 8'h61;
		end
		
		15'h200:					//output- e
		begin
			char <= 8'h65;
		end
		
		15'h400:					//output- l
		begin
			char <= 8'h6c;
		end
		
		15'h800:					//output- space
		begin
			char <= 8'h20;
		end
		
		15'h1000:					//output- ^
		begin
			char <= 8'h5e;
		end
		
		15'h2000:					//output- w
		begin
			char <= 8'h77;
		end
		
		15'h4000:					//output- ^
		begin
			char <= 8'h5e;
		end
		
		
		
		default:
		begin
			char <= 8'h0;
		end
		endcase
end



endmodule