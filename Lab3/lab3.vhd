library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity lab3 is
	port(clock, direction: in std_logic; -- INPUTS
	     step: out std_logic_vector(3 downto 0)); --OUTPUTS
end;

architecture behaviour of lab3 is
begin
	process(clock, direction)
		variable count: std_logic_vector(3 downto 0);
	begin
		if (clock'event and clock = '1') then -- CLK raising edge
			if (direction = '1') then
				case count is
					when "0000" => count := "1010";
					when "1010" => count := "1001";
					when "1001" => count := "0101";
					when "0101" => count := "0110";
					when "0110" => count := "1010";
					when others => count := "0000";
				end case; -- Direction one steps order
			else
				case count is
					when "0000" => count := "0110";
					when "0110" => count := "0101";
					when "0101" => count := "1001";
					when "1001" => count := "1010";
					when "1010" => count := "0110";
					when others => count := "0000";
				end case; -- Direction two steps order
			end if;
			step <= count; -- Asign the step value to OUTPUT
		end if;
	end process;
end behaviour;
