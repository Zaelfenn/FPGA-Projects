module traffic_vsm(
input clk, //clock input
input sen, //sensor input
input rst, //reset input
output reg [2:0] Highway, //farm traffic light
output reg [2:0] Farm //highway traffic light
);
reg [1:0] state; //4 states
reg [2:0] count; //counts up to 8
always @ (posedge clk or negedge rst) //synchronous clock, asynchronous rst
begin

if (~rst)
begin
count <= 3'b000; //reset the count
state <= 2'b00; //default state (farm is red, highway is green)
end
else
begin
case (state)

2'b00: begin//farm red, highway green
if (count < 5)
begin
	count <= count + 1;
	state <= state;
end
else if (~sen) //if a car is detected
begin
	count <= 3'b000; //reset the count
	state <= 2'b10; //change the state
end 
else 
begin
	count <= count;
	state <= state;
end
end 
2'b10:begin  //farm red, highway yellow
if (count == 3) //if there have been 4 cycles
	begin
	count <= 3'b000; //reset the count
	state <= 2'b11; //change the state
	end
else
begin
	count <= count + 1; //add one to the count
	state <= state;
end
end



2'b11:begin //farm green, highway red
if (count == 5)
	begin
	count <= 3'b000; //reset the count
	state <= 2'b01;  //change the state
	end
else
begin
	count <= count + 1; //add one to the count
	state <= state;
end

end

2'b01:begin //farm yellow, highway red
if (count == 3)
	begin
	count <= 3'b000; //reset the count
	state <= 2'b00; //change the state
	end
else
begin
	count <= count + 1; //add one to the count
	state <= state;
end

end

endcase

end

end


always @(state)
begin
case(state)

2'b00: //highway green, farm red
begin
	Highway <= 3'b010; //highway is green
	Farm <= 3'b001; //farm is red
end
2'b01: //highway red, farm yellow
begin
	Highway <= 3'b001; //highway is red
	Farm <= 3'b011; //farm is yellow
end
2'b11: //highway red, farm green
begin
	Highway <= 3'b001; //highway is red
	Farm <= 3'b010; //farm is green
end
2'b10: //highway yellow, farm red
begin
	Highway <= 3'b011; //highway is yellow
	Farm <= 3'b001; //farm is red
end

endcase

end

endmodule