library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

entity TaillightsController is
port(clk,reset,haz,brake,turn_left,turn_right: in std_logic;
		r_light,l_light: out std_logic_vector(0 to 2) 	);
end TaillightsController;

architecture behavioral of TaillightsController is
	type state_type is (IDLE, HAZARD, BLINK_RIGHT, BLINK_LEFT, BRAKE_STATE, BRAKE_RIGHT, BRAKE_LEFT);
	signal STATE : state_type;
	signal COUNT : integer := 0;
	signal RIGHT_LIGHT : std_logic_vector(0 to 2) register;
	signal LEFT_LIGHT : std_logic_vector(0 to 2) register; 
begin
	process (clk)
	begin
	if (clk'event and clk = '1') then
			if(reset = '0') then
				STATE <= IDLE;
			elsif (haz = '1') then
				STATE <= HAZARD;
			else
			case (STATE) is
				when IDLE => 	if(brake = '1' and turn_right = '1') then
										STATE <= BRAKE_RIGHT; --go to 'brake and right' state
									elsif(brake = '1' and turn_left = '1') then
										STATE <= BRAKE_LEFT; --go to 'brake and left' state
									elsif(brake = '1') then
										STATE <= BRAKE_STATE; --go to 'brake' state
									elsif(turn_right = '1') then
										STATE <= BLINK_RIGHT; --go to 'right' state 
									elsif(turn_left = '1') then
										STATE <= BLINK_LEFT; --go to 'left' state
									else
										STATE <= STATE; --reset to 'idle' state
									end if;
				when HAZARD => STATE <= IDLE;
				when BRAKE_STATE => if (turn_right = '1' and brake = '1') then
										STATE <= BRAKE_RIGHT;
									elsif (turn_left = '1' and brake = '1') then
										STATE <= BRAKE_LEFT;
									elsif (turn_right = '1' and brake = '0') then
										STATE <= BLINK_RIGHT;
									elsif(turn_left = '1' and brake = '0') then
										STATE <= BLINK_LEFT;
									elsif(brake = '0') then
										STATE <= IDLE;
									else
										STATE <= STATE;
									end if;
				when BLINK_RIGHT => if (brake = '1' and turn_right = '1') then
											STATE <= BRAKE_RIGHT;
										elsif (brake = '1' and turn_right = '0') then
											STATE <= BRAKE_STATE;
										elsif (turn_right = '0') then
											STATE <= IDLE;
										else
											STATE <= STATE;
										end if;
				when BLINK_LEFT => if (haz = '1') then --blink left state
											STATE <= HAZARD;
										elsif (brake = '1' and turn_left = '1') then
											STATE <= BRAKE_LEFT;
										elsif (brake = '1' and turn_left = '0') then
											STATE <= BRAKE_STATE;
										elsif (turn_left = '0') then
											STATE <= IDLE;
										else
											STATE <= STATE;
										end if;
				when BRAKE_RIGHT => if (brake = '0' and turn_right = '1') then
											STATE <= BLINK_RIGHT;
										elsif (brake = '1' and turn_right = '0') then
											STATE <= BRAKE_STATE;
										elsif (turn_right = '0' and brake = '0') then
											STATE <= IDLE;
										else
											STATE <= STATE;
										end if;
				when BRAKE_LEFT => if (brake = '0' and turn_left = '1') then
											STATE <= BLINK_LEFT;
										elsif (brake = '1' and turn_left = '0') then
											STATE <= BRAKE_STATE;
										elsif (turn_left = '0' and brake = '0') then
											STATE <= IDLE;
										else
											STATE <= STATE;
										end if;
				when others => STATE <= IDLE;
				end case;
		end if;
	end if;
	end process;

	process(clk)
	begin
	if (clk'event and clk = '1') then
		case STATE is 
				when IDLE =>  RIGHT_LIGHT <= "000"; --idle
										LEFT_LIGHT <= "000";
										COUNT <= 0;
										
				when HAZARD => if (RIGHT_LIGHT = "111" and LEFT_LIGHT = "111") then --hazard
											RIGHT_LIGHT <= "000"; 
											LEFT_LIGHT <= "000";
											COUNT <= 0;
										else
											RIGHT_LIGHT <= "111";
											LEFT_LIGHT <= "111";
											COUNT <= 0;
										end if;									
										
				when BRAKE_STATE => RIGHT_LIGHT <= "111"; --brake
										LEFT_LIGHT <= "111";
										COUNT <= 0;
										
				when BLINK_RIGHT =>  case COUNT is --blink right
												when 0 => RIGHT_LIGHT <= "001";
															 LEFT_LIGHT <= "000";
															 count <= count + 1;
												when 1 => RIGHT_LIGHT <= "011";
															 LEFT_LIGHT <= "000";
															 count <= count + 1;
												when 2 => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "000";
															 count <= count + 1;
												when others => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "000";
															 count <= 0;
											end case;
				when BLINK_LEFT => case COUNT is --blink left
												when 0 => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "001";
															 count <= count + 1;
												when 1 => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "011";
															 count <= count + 1;
												when 2 => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "111";
															 count <= count + 1;
												when others => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "000";
															 count <= 0;
												end case;
				when BRAKE_RIGHT => case COUNT is --brake right
												when 0 => RIGHT_LIGHT <= "001";
															 LEFT_LIGHT <= "111";
															 count <= count + 1;
												when 1 => RIGHT_LIGHT <= "011";
															 LEFT_LIGHT <= "111";
															 count <= count + 1;
												when 2 => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "111";
															 count <= count + 1;
												when others => RIGHT_LIGHT <= "000";
															 LEFT_LIGHT <= "111";
															 count <= 0;
												end case;
				when BRAKE_LEFT => case COUNT is --brake left
												when 0 => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "001";
															 count <= count + 1;
												when 1 => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "011";
															 count <= count + 1;
												when 2 => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "111";
															 count <= count + 1;
												when others => RIGHT_LIGHT <= "111";
															 LEFT_LIGHT <= "000";
															 count <= 0;
												end case;
				when others => RIGHT_LIGHT <= "000"; --error state
									LEFT_LIGHT <= "000";
									count <= 0;
			end case;
		end if;
	r_light <= RIGHT_LIGHT;
	l_light <= LEFT_LIGHT;
	end process;
end behavioral;