module Encrypt_Decrypt(
input [7:0] key1,
input [7:0] key2,
input [7:0] text_in,
input decrypt,
input ready,
output reg [7:0] text_out
);

reg [7:0] ip, ep_1, ep_2, tempResult;
reg [3:0] p_0, p_1, p4_result_1, p4_result_2;
reg [7:0] k1, k2;
reg [1:0] s1_row, s1_column, s0_row, s0_column, s1_out, s0_out;

function [3:0] p4;
	input [1:0] s0_row, s0_column, s1_row, s1_column;
	begin
		case(s0_row)
		2'b00	:	begin //row 0
			case(s0_column)
					2'b00: s0_out = 2'b01;
					2'b01: s0_out = 2'b00;
					2'b10: s0_out = 2'b11;
					2'b11: s0_out = 2'b10;
				endcase
			end
		2'b01	:	begin //row 1
			case(s0_column)
					2'b00: s0_out = 2'b11;
					2'b01: s0_out = 2'b10;
					2'b10: s0_out = 2'b01;
					2'b11: s0_out = 2'b00;
				endcase
			end
		2'b10	:	begin //row 2
			case(s0_column)
					2'b00: s0_out = 2'b00;
					2'b01: s0_out = 2'b10;
					2'b10: s0_out = 2'b01;
					2'b11: s0_out = 2'b11;
				endcase
			end
		2'b11	:	begin //row 3
			case(s0_column)
					2'b00: s0_out = 2'b11;
					2'b01: s0_out = 2'b01;
					2'b10: s0_out = 2'b11;
					2'b11: s0_out = 2'b10;
			endcase
			end
		endcase
	
	case(s1_row)
		2'b00	:	begin //row 0
			case(s1_column)
					2'b00: s1_out = 2'b00;
					2'b01: s1_out = 2'b01;
					2'b10: s1_out = 2'b10;
					2'b11: s1_out = 2'b11;
				endcase
			end
		2'b01	:	begin //row 1
			case(s1_column)
					2'b00: s1_out = 2'b10;
					2'b01: s1_out = 2'b00;
					2'b10: s1_out = 2'b01;
					2'b11: s1_out = 2'b11;
				endcase
			end
		2'b10	:	begin //row 2
			case(s1_column)
					2'b00: s1_out = 2'b11;
					2'b01: s1_out = 2'b00;
					2'b10: s1_out = 2'b01;
					2'b11: s1_out = 2'b00;
				endcase
			end
		2'b11	:	begin //row 3
			case(s1_column)
					2'b00: s1_out = 2'b10;
					2'b01: s1_out = 2'b01;
					2'b10: s1_out = 2'b00;
					2'b11: s1_out = 2'b11;
				endcase
			end
	endcase
	
	p4 = {s0_out[0], s1_out[0], s1_out[1], s0_out[1]};
	end
	endfunction
	

always @ (ready or decrypt)
begin
	ip = {text_in[6], text_in[2], text_in[5], text_in[7], text_in[4], text_in[0], text_in[3], text_in[1]};
	ep_1 = {ip[0], ip[3], ip[2], ip[1], ip[2], ip[1], ip[0], ip[3]};
	
	
<<<<<<< HEAD
	if(!decrypt) begin
=======
	if(decrypt) begin
>>>>>>> b17b5f4c807e6a2a9dbd781dafd120a94388da25
		p_0 = {ep_1[7] ^ key2[7], ep_1[6] ^ key2[6], ep_1[5] ^ key2[5], ep_1[4] ^ key2[4]};
		p_1 = {ep_1[3] ^ key2[3], ep_1[2] ^ key2[2], ep_1[1] ^ key2[1], ep_1[0] ^ key2[0]};
	end
	else begin
		p_0 = {ep_1[7] ^ key1[7], ep_1[6] ^ key1[6], ep_1[5] ^ key1[5], ep_1[4] ^ key1[4]};
		p_1 = {ep_1[3] ^ key1[3], ep_1[2] ^ key1[2], ep_1[1] ^ key1[1], ep_1[0] ^ key1[0]};
	end
	
	s0_row = {p_0[3], p_0[0]};
	s0_column = {p_0[2], p_0[1]};
	s1_row = {p_1[3], p_1[0]};
	s1_column = {p_1[2], p_1[1]};
	
	p4_result_1 = p4(s0_row, s0_column, s1_row, s1_column);
	
	p4_result_1 = {p4_result_1[3] ^ ip[7], p4_result_1[2] ^ ip[6], p4_result_1[1] ^ ip[5], p4_result_1[0] ^ ip[4]};
	ep_2 = {p4_result_1, ip[3], ip[2], ip[1], ip[0]};
	ep_2 = {ep_2[4], ep_2[7], ep_2[6], ep_2[5], ep_2[6], ep_2[5], ep_2[4], ep_2[7]};
	

<<<<<<< HEAD
	if(!decrypt) begin
=======
	if(decrypt) begin
>>>>>>> b17b5f4c807e6a2a9dbd781dafd120a94388da25
		p_0 = {ep_2[7] ^ key1[7], ep_2[6] ^ key1[6], ep_2[5] ^ key1[5], ep_2[4] ^ key1[4]};
		p_1 = {ep_2[3] ^ key1[3], ep_2[2] ^ key1[2], ep_2[1] ^ key1[1], ep_2[0] ^ key1[0]};
	end
	else begin
		p_0 = {ep_2[7] ^ key2[7], ep_2[6] ^ key2[6], ep_2[5] ^ key2[5], ep_2[4] ^ key2[4]};
		p_1 = {ep_2[3] ^ key2[3], ep_2[2] ^ key2[2], ep_2[1] ^ key2[1], ep_2[0] ^ key2[0]};
	end
	
	s0_row = {p_0[3], p_0[0]};
	s0_column = {p_0[2], p_0[1]};
	s1_row = {p_1[3], p_1[0]};
	s1_column = {p_1[2], p_1[1]};
	
	
	p4_result_2 = p4(s0_row, s0_column, s1_row, s1_column);
	
	p4_result_2 = {p4_result_2[3] ^ ip[3], p4_result_2[2] ^ ip[2], p4_result_2[1] ^ ip[1], p4_result_2[0] ^ ip[0]};
	
	tempResult = {p4_result_2, p4_result_1};

<<<<<<< HEAD
=======
	//tempResult = {tempResult[4], tempResult[7], tempResult[6], tempResult[5], 
		//tempResult[6], tempResult[5], tempResult[4], tempResult[7]};
		
	//text_out = tempResult;

>>>>>>> b17b5f4c807e6a2a9dbd781dafd120a94388da25
	text_out = {tempResult[4], tempResult[7], tempResult[5], tempResult[3], 
		tempResult[1], tempResult[6], tempResult[0], tempResult[2]};
end

endmodule