library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity Keyboard is

port( 
	CLK: in std_logic; -- Clock input
	ir: in std_logic; -- Reset input
	Col: in std_logic_vector ( 2 downto 0 ); -- Keypad column input
	Row: inout std_logic_vector ( 3 downto 0 ); -- Keypad row output
	Q: out std_logic_vector ( 3 downto 0 )); -- BCD output

end;

architecture Behaviour of Keyboard is
	signal pulse: std_logic; -- Pulse detector
begin
	process(CLK) -- Ring counter
		variable rowtemp: std_logic_vector(3 downto 0); 
	begin 
		
		if(CLK'event and CLK = '1') then
			if(ir = '1') then rowtemp := "0001"; -- Synchronous reset
			else
				rowtemp := rowtemp(2 downto 0) & rowtemp(3); -- Shift
			end if;
		end if;
		Row <= rowtemp;
	end process;

	pulse <= Col(2) or Col(1) or Col(0); -- Pulse detector

	process(CLK) -- Key detector and BCD output
		variable outtemp: std_logic_vector(3 downto 0);
	begin
		if(CLK'event and CLK = '1' and pulse = '1') then
			case Row is 
				when "0001" => 
					if (Col = "001") then outtemp := "0001";
					elsif(Col = "010") then outtemp := "0010";
					elsif(Col = "100") then outtemp := "0011";
					end if;
				when "0010" => 
					if (Col = "001") then outtemp := "0100";
					elsif(Col = "010") then outtemp := "0101";
					elsif(Col = "100") then outtemp := "0110";
					end if;
				when "0100" => 
					if (Col = "001") then outtemp := "0111";
					elsif(Col = "010") then outtemp := "1000";
					elsif(Col = "100") then outtemp := "1001";
					end if;
				when "1000" => 
					if (Col = "001") then outtemp := "1010";
					elsif(Col = "010") then outtemp := "0000";
					elsif(Col = "100") then outtemp := "1011";
					end if;
				when others => NULL;
			end case;
		end if;
	Q <= outtemp;
	end process;
end Behaviour;
