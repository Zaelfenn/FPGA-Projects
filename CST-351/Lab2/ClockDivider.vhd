library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;
  
entity ClockDivider is
generic (DIV: natural:=12500000);
port ( clk,reset: in std_logic;
		clock_out: out std_logic);
end ClockDivider;
  
architecture behavioral of ClockDivider is
signal count: integer:=0;
signal temp : std_logic := '0';
  
begin
process(clk,reset)
begin	
	if(reset='0') then
		count <= 0;
		temp <= '0';
		
	elsif(clk'event and clk= '1') then
		count <= count+1;
		
		if (count >= DIV) then
			temp <= NOT temp;
			count <= 0;
		
		end if;
	end if;
clock_out <= temp;

end process;
  
end behavioral;