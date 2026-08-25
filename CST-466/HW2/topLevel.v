module topLevel(
<<<<<<< HEAD
	input [9:0] data_in, //switches 9-0, used to enter the values
	//input [3:0] text_in,
	input decrypt,
	input encrypt, 
	input keyIn,
	input textIn,
	output [6:0] key1_1,
	output [6:0] key1_2,
	output [6:0] key2_1,
	output [6:0] key2_2,
	output [6:0] out_1,
	output [6:0] out_2
	);
	
	wire [9:0]tempKeyIn, tempKey;
	wire [7:0]tempTextIn, tempKey1, tempKey2, tempOut;
	
	decideInput 	U1	(keyIn, textIn, data_in, tempKeyIn, tempTextIn);
	KeyGen			U2	(tempKeyIn, tempKey1, tempKey2);
	
	hexToSSEG		U3	(tempKey1[7:4], key1_1);
	hexToSSEG		U4	(tempKey1[3:0], key1_2);
	hexToSSEG		U5	(tempKey2[7:4], key2_1);
	hexToSSEG		U6	(tempKey2[3:0], key2_2);
	
	Encrypt_Decrypt	U7		(tempKey1, tempKey2, tempTextIn, decrypt, encrypt, tempOut);
	hexToSSEG		U8	(tempOut[7:4], out_1);
	hexToSSEG		U9	(tempOut[3:0], out_2);
=======
	input [7:0] key1,
	input [7:0] key2,
	input [7:0] text_in,
	input decrypt,
	output [7:0] out
	);
	
	//wire [7:0] out;
	
	Encrypt_Decrypt	U1	(key1, key2, text_in, decrypt, out);
>>>>>>> b17b5f4c807e6a2a9dbd781dafd120a94388da25
	
	endmodule