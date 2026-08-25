module keypad_check_sm(
input clk,
input rst,
input [3:0] col_check,
output reg [3:0] row_check,
output reg [3:0] dout,
output reg ena
);


reg [10:0] state;
always @(posedge clk)
begin
	case(row_check)
		4'he:					//0111
			begin
				row_check <= 4'hd;
				casex(col_check)
					4'bxxx0:
					begin
						dout <= 4'b0001;		//row 1, col 1 = 1
						ena <= 1'b1;
					end
					4'bxx01: 					//row 1, col 2 = 2
					begin
						dout <= 4'b0010;
						ena <= 1'b1;
					end
					4'bx011: 					//row 1, col 3 = 3
					begin
						dout <= 4'b0011;
						ena <= 1'b1;
					end
					4'b0111:						//row 1, col 4 = a
					begin
						dout <= 4'b1010;
						ena <= 1'b1;
					end
					default: 					//no output
					begin
						dout <= 4'b0;
						ena <= 1'b0;
					end
				endcase
			end
			
		4'hd:					//1011
			begin
				row_check <= 4'hb;
				casex(col_check)
					4'bxxx0:							//row 2, col 1 = 4
					begin
						dout <= 4'b0100;	
						ena <= 1'b1;
					end
					4'bxx01: 						//row 2, col 2 = 5
					begin
						dout <= 4'b0101;
						ena <= 1'b1;
					end
					4'bx011: 						//row 2, col 3 = 6
					begin
						dout <= 4'b0110;
						ena <= 1'b1;
					end
					4'b0111:							//row 2, col 4 = b
					begin
						dout <= 4'b1011;
						ena <= 1'b1;
					end
					default: 
					begin
						dout <= 4'b0;
						ena <= 1'b0;
					end
				endcase
			end
			
		4'hb:					//1101
			begin
				row_check <= 4'h7;
				casex(col_check)
					4'bxxx0:							//row 3, col 1 = 7
					begin
						dout <= 4'b0111;
						ena <= 1'b1;
					end
					4'bxx01: 						//row 3, col 2 = 8
					begin
						dout <= 4'b1000;
						ena <= 1'b1;
					end
					4'bx011: 						//row 3, col 3 = 9
					begin
						dout <= 4'b1001;
						ena <= 1'b1;
					end
					4'b0111:							//row 3, col 4 = c
					begin
						dout <= 4'b1100;
						ena <= 1'b1;
					end
					default: 
					begin
						dout <= 4'b0;
						ena <= 1'b0;
					end
				endcase
			end
			
		4'h7:					//1110
			begin
				row_check <= 4'he;
				casex(col_check)
					4'bxxx0:							//row 4, col 1 = * (15)
					begin
						dout <= 4'b1111;
						ena <= 1'b1;
					end
					4'bxx01: 						//row 4, col 2 = 0
					begin
						dout <= 4'b0;
						ena <= 1'b1;
					end
					4'bx011: 						//row 4, col 3 = # (14)
					begin
						dout <= 4'b1110;
						ena <= 1'b1;
					end
					4'b0111:							//row 4, col 4 = d
					begin
						dout <= 4'b1101;
						ena <= 1'b1;
					end
					default: 
					begin
						dout <= 4'b0;
						ena <= 1'b0;
					end
				endcase
			end
			
		default:
			begin
				row_check <= 4'h7;
				ena <= 1'b0;
			end
	endcase
end

endmodule