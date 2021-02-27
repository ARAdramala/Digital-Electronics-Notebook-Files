library ieee;
use ieee.std_logic_1164.all;

entity temperature is
	port(temp: in std_logic_vector(3 downto 0); -- Input 4bit temp vector
		led: out std_logic_vector(2 downto 0)); -- Output 3 bit sensor vector

end temperature;

architecture arc1 of temperature is
begin
	process (temp)
	begin
		if (temp <= "1000") then led(0) <= '1'; led(1) <= '0'; led(2) <= '0';
		elsif (temp <= "1010") then led(0) <= '0'; led(1) <= '1'; led(2) <= '0';
		else led(0) <= '0'; led(1) <= '0'; led(2) <= '1';
		end if;  -- led(0): Too cold; led(1): Just right; led(2): Too hot;
	end process;

end arc1;

