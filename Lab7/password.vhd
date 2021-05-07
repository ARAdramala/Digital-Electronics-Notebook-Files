library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Password is

port( 
	key: in std_logic_vector ( 3 downto 0 ); -- Data input
	CLK: in std_logic ;	-- Clock signal
	addr: out std_logic_vector ( 1 downto 0 ); -- Address output
	data: out std_logic_vector ( 3 downto 0 ); -- Data output
	cs: out std_logic ); -- Enable

end;

architecture Behaviour of Password is
	type state_type is (Q0, Q1, Q2, Q3); -- States datatype
	signal state : state_type;  -- States
begin
	process(CLK) -- Synchronous process
	begin
		if(CLK'event and CLK = '1') then -- If CLK rising edge then
			case state is 
				when Q0 => addr <= "00"; -- State Q0
					cs <= '1';
					if(key = "1010") then state <= Q1;
					else state <= Q0;
					end if;
				
				when Q1 => addr <= addr; -- State Q1
					cs <= '0';
					data <= key;
					if (key = "1010") then state <= Q1;
					elsif (key = "1011") then state <= Q0;
					else state <= Q2;
					end if;
						
				when Q2 => addr <= addr; -- State Q2
					cs <= '1';
					if (key = data) then state <= Q2;
					elsif (key = "1011") then state <= Q0;
					else state <= Q3;
					end if;
		
				when Q3 => addr <= addr + 1; -- State Q3
					state <= Q1;
				
				when others => state <= Q0; -- Backup --> State Q0
			end case;
		end if;
	end process;			
end Behaviour;

