library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity StepperEncoder is
	port(	entrada:  in std_logic_vector(1 downto 0); -- Encoder input
		clk, rst: in std_logic;	-- Clock and reset inputs
		stepper: out std_logic_vector(3 downto 0)); -- Stepper output
end;

architecture Behaviour of StepperEncoder is
	type state_type is (Q0, Q1, Q2, Q3); -- Define State datatype
	signal state : state_type; -- Define state as a state_type signal
begin

	process(clk, rst) 
	begin 
		if (rst = '0') then state <= Q0; stepper <= "0000"; -- Reset
		elsif rising_edge(clk) then 
			case state is
				when Q0 => stepper <= "0110"; -- Output for state 0
					if (entrada = "01") then state <= Q1; -- Change to state 1
					elsif (entrada = "10") then state <= Q3; -- Change to state 3
					else state <= Q0; -- Else remain in this state
					end if;
				when Q1 => stepper <= "1010"; -- Output for state 1
					if(entrada = "11") then state <= Q2; -- Change to state 2
					elsif (entrada = "00") then state <= Q0; -- Change to state 0
					else state <= Q1; -- Else remain in this state
					end if; 
				when Q2 => stepper <= "1001"; -- Output for state 2
					if (entrada = "10") then state <= Q3; -- Change to state 3
					elsif (entrada = "01") then state <= Q1; -- Change to state 1
					else state <= Q2; -- Else remain in this state
					end if;
				when Q3 => stepper <= "0101"; -- Output for state 3
					if(entrada = "00") then state <= Q0; -- Change to state 0
					elsif (entrada = "11") then state <= Q2; -- Change to state 2
					else state <= Q3; -- Else remain in this state
					end if; 
			end case;
		end if;
	end process;
end Behaviour;

