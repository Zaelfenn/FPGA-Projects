module SevenSegDeMux(               
input [1:0] sel,				//select bits
input [6:0] lights,			//seven seg output 
output reg [11:0] dout			//demux out, there are 12 bits for the seven seg
);


								/*
									dout:
								  bit 11: selects digit 1 for output (active low)
								  bit 10: Active High A(hex0[0])
								  bit 9: Active High F(hex0[5])
								  bit 8: selects digit 2 for output	(active low)
								  bit 7: selects digit 3 for output	(active low)
								  bit 6: Active High B(hex0[1])
								  bit 5: selects digit 4 for output	(active low)
								  bit 4: Active High G(hex0[6])
								  bit 3: Active High C(hex0[2])
								  bit 2: dot
								  bit 1: Active High D(hex0[3])
								  bit 0: Active High E(hex0[4])
								*/

always @ (sel or lights) 
begin

	case (sel)
		2'b00: //digit 1
		begin
			dout[11] <= 1'b0;
			dout[8:7] <= 2'b11;
			dout[5] <= 1'b1;
			dout[10] <= lights[0];
			dout[9] <= lights[5];
			dout[6] <= lights[1];
			dout[4] <= lights[6];
			dout[3] <= lights[2];
			dout[2] <= 1'b0; 			//keep the dot off always
			dout[1] <= lights[3];
			dout[0] <= lights[4];
		end
		
		2'b01: //digit 2
		begin
			dout[11] <= 1'b1;
			dout[8:7] <= 2'b01;			
			dout[5] <= 1'b1;	
			dout[10] <= lights[0];
			dout[9] <= lights[5];
			dout[6] <= lights[1];
			dout[4] <= lights[6];
			dout[3] <= lights[2];
			dout[2] <= 1'b0; 			//keep the dot off always
			dout[1] <= lights[3];
			dout[0] <= lights[4];
		end
		
		2'b10: //digit 3
		begin
			dout[11] <= 1'b1;
			dout[8:7] <= 2'b10;
			dout[5] <= 1'b1;
			dout[10] <= lights[0];
			dout[9] <= lights[5];
			dout[6] <= lights[1];
			dout[4] <= lights[6];
			dout[3] <= lights[2];
			dout[2] <= 1'b0; 			//keep the dot off always
			dout[1] <= lights[3];
			dout[0] <= lights[4];
		end
		
		2'b11: //digit 4
		begin
			dout[11] <= 1'b1;
			dout[8:7] <= 2'b11;
			dout[5] <= 1'b0;
			dout[10] <= lights[0];
			dout[9] <= lights[5];
			dout[6] <= lights[1];
			dout[4] <= lights[6];
			dout[3] <= lights[2];
			dout[2] <= 1'b0; 			//keep the dot off always
			dout[1] <= lights[3];
			dout[0] <= lights[4];
		end

	endcase
	

end

endmodule