library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity PWM is
	port (clk: in std_logic; -- CLK input
		ref: in integer range 0 to 15; -- Reference input
		q: out integer range 0 to 15; -- Count output
		led: out integer range 0 to 1); -- PWM ouput
end PWM;

architecture behaviour of PWM is
begin
	process(clk)
		variable count: integer range 0 to 15;
		variable state: integer range 0 to 1;
		variable top: integer range 0 to 1;
	begin
		if(clk'event and clk = '1') then
			if(top = 0) then -- If counter in adding mode
				count := count + 1;
			elsif(top = 1) then -- If counter in substracting
				count := count - 1;
			end if;

			if (count = 15) then -- If counter max value
				top := 1; -- Substracting mode
			elsif(count = 0) then -- If min value
				top := 0; -- Adding mode
			else -- For every other value
				top := top; -- Don't change mode
			end if;
		end if;
		q <= count;

		if (q >= ref) then -- Count >= Reference
			state := 1; -- PWM -> HIGH
		elsif (q < ref) then -- Count < Reference
			state := 0; -- PWM -> LOW
		end if;
		led <= state;
	end process;
end behaviour;

