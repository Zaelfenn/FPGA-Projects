module KeyGen(
input [9:0] key_in,
output reg [7:0] key1,
output reg [7:0] key2
);

reg [4:0] key1_u, key1_l, key2_u, key2_l;

always @ (*)
begin
	key1_u = {key_in[5], key_in[8], key_in[3], key_in[6], key_in[7]};
	key1_l = {key_in[9], key_in[1], key_in[2], key_in[4], key_in[0]};
	
	key2_u = {key1_u[2:0], key1_u[4:3]};
	key2_l = {key1_l[2:0], key1_l[4:3]};
	
	key1 = {key1_l[4], key1_u[2], key1_l[3], key1_u[1], key1_l[2], key1_u[0], key1_l[0], key1_l[1]};
	key2 = {key2_l[4], key2_u[2], key2_l[3], key2_u[1], key2_l[2], key2_u[0], key2_l[0], key2_l[1]};
end

endmodule