-- uart.vhd: UART controller - receiving part
-- Author(s): xmikhe00
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-------------------------------------------------
entity UART_RX is
port(	
    CLK: 	    in std_logic;
	RST: 	    in std_logic;
	DIN: 	    in std_logic;
	DOUT: 	    out std_logic_vector(7 downto 0);
	DOUT_VLD: 	out std_logic
);
end UART_RX;  
-------------------------------------------------
architecture behavioral of UART_RX is
	signal iclk			:	std_logic_vector (4 downto 0) := "00000";
	signal ncnt			:	std_logic_vector (3 downto 0) := "0000";
	signal time_vld		:	std_logic;
	signal record_vld	:	std_logic;
	signal dout_save	: 	std_logic_vector (7 downto 0);
begin
	FSM : entity work.UART_FSM(behavioral)
		port map (
		   DIN		=>	DIN,
		   CLK     	=>	CLK,
		   RST      =>	RST,
		   ICLK     =>	iclk,	
		   NCNT		=>	ncnt,  
		   T_VLD	=>	time_vld,  
		   R_VLD	=>	record_vld,
		   D_VLD 	=>	DOUT_VLD
		   );
-------------------------------------------------------
	inter_clock : process (CLK) begin
		if (CLK'event and CLK = '1') then
			if (time_vld = '1') then
				if (record_vld = '1') then 
					if (iclk = "01111") then
						iclk <= "00000";
					else
						iclk <= iclk + 1;
					end if;
				else
					if (iclk = "10110") then 
						iclk <= "00000";
					else
						iclk <= iclk + 1;
					end if;
				end if;
			else 
				iclk <= "00000";
			end if;
		end if;
	end process inter_clock;
-------------------------------------------------------
	numerical_counter : process (CLK) begin
		if (CLK'event and CLK = '1') then
			if (record_vld = '1') then
				if (record_vld = '1' and iclk = "01111") then
					ncnt <= ncnt + 1;
				end if;
			else 
				ncnt <= "0000";
			end if;
		end if;
	end process numerical_counter;
------------------------------------------------------------
	date_out : process (ncnt, record_vld) begin 
		if (record_vld = '1') then 
			case ncnt is
				when "0000"		=>		dout_save(0)		<= 		DIN;			
				when "0001"		=>		dout_save(1)		<= 		DIN;
				when "0010"		=>		dout_save(2)		<= 		DIN;
				when "0011"		=>		dout_save(3)		<= 		DIN;
				when "0100"		=>		dout_save(4)		<= 		DIN;
				when "0101"		=>		dout_save(5)		<= 		DIN;
				when "0110"		=>		dout_save(6)		<= 		DIN;
				when "0111"		=>		dout_save(7)		<= 		DIN;
				when others		=> 		NULL;
			end case;
		end if;
	end process date_out;
------------------------------------------------------------
	reg0: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(0) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(0) <= dout_save(0);
		end if;
	end process reg0;
	------------------------------------------------------------
	reg1: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(1) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(1) <= dout_save(1);
		end if;
	end process reg1;
	------------------------------------------------------------
	reg2: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(2) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(2) <= dout_save(2);
		end if;
	end process reg2;
	------------------------------------------------------------
	reg3: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(3) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(3) <= dout_save(3);
		end if;
	end process reg3;
	------------------------------------------------------------
	reg4: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(4) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(4) <= dout_save(4);
		end if;
	end process reg4;
	------------------------------------------------------------
	reg5: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(5) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(5) <= dout_save(5);
		end if;
	end process reg5;
	------------------------------------------------------------
	reg6: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(6) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(6) <= dout_save(6);
		end if;
	end process reg6;
	------------------------------------------------------------
	reg7: process (CLK,RST) begin
		if (RST = '1') then
			DOUT(7) <= '0';
		elsif (CLK'event and CLK = '1') then
			DOUT(7) <= dout_save(7);
		end if;
	end process reg7;
------------------------------------------------------------
end behavioral;
