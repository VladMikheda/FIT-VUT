-- uart_fsm.vhd: UART controller - finite state machine
-- Author(s): xmikhe00
--
library ieee;
use ieee.std_logic_1164.all;
-------------------------------------------------
entity UART_FSM is
port(
   DIN      :  in std_logic;
   CLK      :  in std_logic;
   RST      :  in std_logic;
   ICLK     :  in std_logic_vector(4 downto 0); 
   NCNT     :  in std_logic_vector(3 downto 0);
   T_VLD    :  out std_logic;
   R_VLD    : 	out std_logic;
   D_VLD    :  out std_logic
   );
end entity UART_FSM;
-------------------------------------------------
architecture behavioral of UART_FSM is
type state_type is (WAIT_START,START_BIT,RECORDING_DATA,WAIT_STOP,STOP_BIT);
signal state : state_type := WAIT_START; 
begin
-------------------------------------------------   
   inter_logic : process (CLK) begin
      if (CLK'event and CLK = '1') then 
         if RST = '1' then
            state <= WAIT_START;
         else 
            case state is
               when WAIT_START         =>    if DIN = '0' then
                                             state <= START_BIT;
                                             end if;
               when START_BIT          =>    if ICLK = "10110" then
                                             state <= RECORDING_DATA;
                                             end if;
               when RECORDING_DATA     =>    if NCNT = "0111" then 
                                             state <= WAIT_STOP;               
                                             end if;
               when WAIT_STOP          =>    if ICLK = "01111" then 
                                             state <= STOP_BIT;
                                             end if;
               when STOP_BIT           =>    if DIN = '1' then 
                                             state <= WAIT_START;
                                             end if;
               when others             =>    NULL;
            end case;
         end if;
      end if;
   end process inter_logic;
--------------------------------------------------  
out_logic : process (CLK) begin
   if (state = START_BIT or state = RECORDING_DATA or state = WAIT_STOP) then
      T_VLD <= '1';
      D_VLD <= '0';
      if (state = RECORDING_DATA) then 
         R_VLD <= '1';
      else
         R_VLD <= '0';
      end if;
   else
      T_VLD <= '0';
      if (state = STOP_BIT) then
         D_VLD <= '1';
      else
         D_VLD <= '0';
      end if;
   end if;
end process out_logic;
--------------------------------------------------
end behavioral;
