-- cpu.vhd: Simple 8-bit CPU (BrainLove interpreter)
-- Copyright (C) 2021 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Vladislav Mikheda (xmikhe00)
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
 port (
   CLK   : in std_logic;  -- hodinovy signal
   RESET : in std_logic;  -- asynchronni reset procesoru
   EN    : in std_logic;  -- povoleni cinnosti procesoru

   -- synchronni pamet ROM
   CODE_ADDR : out std_logic_vector(11 downto 0); -- adresa do pameti
   CODE_DATA : in std_logic_vector(7 downto 0);   -- CODE_DATA <- rom[CODE_ADDR] pokud CODE_EN='1'
   CODE_EN   : out std_logic;                     -- povoleni cinnosti

   -- synchronni pamet RAM
   DATA_ADDR  : out std_logic_vector(9 downto 0); -- adresa do pameti
   DATA_WDATA : out std_logic_vector(7 downto 0); -- ram[DATA_ADDR] <- DATA_WDATA pokud DATA_EN='1'
   DATA_RDATA : in std_logic_vector(7 downto 0);  -- DATA_RDATA <- ram[DATA_ADDR] pokud DATA_EN='1'
   DATA_WREN  : out std_logic;                    -- cteni z pameti (DATA_WREN='0') / zapis do pameti (DATA_WREN='1')
   DATA_EN    : out std_logic;                    -- povoleni cinnosti

   -- vstupni port
   IN_DATA   : in std_logic_vector(7 downto 0);   -- IN_DATA obsahuje stisknuty znak klavesnice pokud IN_VLD='1' a IN_REQ='1'
   IN_VLD    : in std_logic;                      -- data platna pokud IN_VLD='1'
   IN_REQ    : out std_logic;                     -- pozadavek na vstup dat z klavesnice

   -- vystupni port
   OUT_DATA : out  std_logic_vector(7 downto 0);  -- zapisovana data
   OUT_BUSY : in std_logic;                       -- pokud OUT_BUSY='1', LCD je zaneprazdnen, nelze zapisovat,  OUT_WREN musi byt '0'
   OUT_WREN : out std_logic                       -- LCD <- OUT_DATA pokud OUT_WE='1' a OUT_BUSY='0'
 );
end cpu;


-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is

--PC
  signal pc_reg        : std_logic_vector (11 downto 0) :="000000000000"; -- register citace instrukci
  signal pc_inc        : std_logic;                                       -- inkrementace primarniho citace
  signal pc_dec        : std_logic;                                       -- dekrementace primarniho citace
--PC

--CNT
  signal cnt_reg        : std_logic_vector (11 downto 0) :="000000000000"; -- register citace
  signal cnt_inc        : std_logic;                                       -- inkrementace primarniho citace
  signal cnt_dec        : std_logic;                                       -- dekrementace primarniho citace
--CNT

-- PTR
  signal ptr_reg       : std_logic_vector (9 downto 0) := "0000000000"; -- register jednotki ve kterem se chranena adresa RAM 
  signal ptr_inc       : std_logic;                                     -- inkrementace ptr RAM
  signal ptr_dec       : std_logic;                                     -- dekrementace ptr RAM
-- PTR

--MUX
  signal mux_select    : std_logic_vector (1 downto 0) := "00";         -- signal ktery nastavi vstup do multiplexeru
  signal mux_out       : std_logic_vector (7 downto 0) := "00000000";
--MUX

--FSM
type fsm_type is (
  --s_fsm_load,
  s_fetch,                                     -- stav nacteni instrukce
--
  s_decode,                                    -- stav dekodirovani instrukce
--
  s_ptr_inc,                                   -- stav inkrementace ukazatelu ve kterem je adresa RAM 
  s_ptr_dec,                                   -- stav dekrementace ukazatelu ve kterem je adresa RAM 
--
  s_data_inc_0,                                -- stav inkrementace dat ve bunce RAM #0
  s_data_inc_1,                                -- stav inkrementace dat ve bunce RAM #1
--  
  s_data_write_ram,                            -- stav zapisu do RAM 
--
  s_data_dec_0,                                -- stav dekrementace dat ve bunce RAM #0
  s_data_dec_1,                                -- stav dekrementace dat ve bunce RAM #1
--
  s_dis_out_0,                                 -- stav vystupu na displej dat #0
  s_dis_out_1,                                 -- stav vystupu na displej dat #1
--
  s_dis_in_0,                                  -- stav nacteni z klavisnicy dat #0
  s_dis_in_1,                                  -- stav nacteni z klavisnicy dat #1
--
  s_l_loop_0,                                  -- stav zacatku cyklu
  s_l_loop_1,                                  -- stav kontrolovani podminek cyklu
  s_l_loop_2,                                  -- stav kontrolovani ukonceni nebo pokracovani behu ve ciklu
  s_l_loop_3,                                  -- stav nacteni priste instrukce pro cyklus
--
  s_r_loop_0,                                  -- stav zacatku skoku na zacatek cyklu
  s_r_loop_1,                                  -- stav kontrolovani podminek skoku
  s_r_loop_2,                                  -- stav nacteni minule instrukce pro cyklus
  s_r_loop_3,                                  -- stav kontrolovani ukonceni nebo pokracovani skoku
  s_r_loop_4,                                  -- stav pokracovani ve ciklu nebo ve skoku
--
  s_break_0,                                   -- stav ukonceni ciklu
  s_break_1,                                   -- stav nacteni priste instrukce pro ukonceni ciklu
  s_break_2,                                   -- stav kontrolovani ukonceni
--
  s_prog_stop,                                 -- stav ukonceni behu programy
  --
  s_wait                                       -- stav cekani na priste instrukci
  );
signal fsm_state  : fsm_type := s_fetch;       -- stav automatu
signal fsm_next_state  : fsm_type;             -- priste stav automatu
--FSM




begin

-- PC
  pc: process (RESET, CLK,pc_inc,pc_dec) begin
    if RESET='1' then
      pc_reg <= (others=>'0');
    elsif CLK'event and CLK='1' then
      if pc_inc = '1' then
        pc_reg <= pc_reg + 1;
      elsif pc_dec = '1' then
        pc_reg <= pc_reg - 1;
      end if;
    end if;
  end process;

  CODE_ADDR <= pc_reg;
-- PC



-- CNT
cnt: process (RESET, CLK, cnt_inc, cnt_dec) begin
  if RESET='1' then
    cnt_reg <= (others=>'0');
  elsif CLK'event and CLK='1' then
    if cnt_inc = '1' then
      cnt_reg <= cnt_reg + 1;
    elsif cnt_dec = '1' then
      cnt_reg <= cnt_reg - 1;
    end if;
  end if;
end process;
-- CNT

-- PTR
ptr: process (RESET, CLK, ptr_inc, ptr_dec) begin
  if RESET='1' then
    ptr_reg <= (others=>'0');
  elsif CLK'event and CLK='1' then
    if ptr_inc='1' then
      ptr_reg <= ptr_reg + 1;
    elsif ptr_dec='1' then
      ptr_reg <= ptr_reg - 1;
    end if;
  end if;
end process;

DATA_ADDR <= ptr_reg;
-- PTR

--MUX
mux: process (RESET, CLK, mux_select) begin
  if RESET='1' then
    mux_out <= (others=>'0');
  elsif CLK'event and CLK='1' then
    case(mux_select) is
      when "10" => mux_out <= IN_DATA;
      when "01" => mux_out <= DATA_RDATA + 1;
      when "11" => mux_out <= DATA_RDATA - 1;
      when others => mux_out <= (others=>'0');
      end case;
  end if;
end process;

DATA_WDATA <= mux_out;
--MUX

OUT_DATA <= DATA_RDATA;


--FSM
fsm_inter_logic : process (CLK, EN, RESET) begin
  if CLK'event and CLK = '1' then
     if RESET = '1' then
        fsm_state <= s_fetch;
      elsif EN = '1' then
        fsm_state <= fsm_next_state;
     end if;
  end if;
end process;

fsm_out_put_logic : process (OUT_BUSY,CODE_DATA,DATA_RDATA,IN_VLD,cnt_reg,fsm_state) begin
-------------------------------------------init-----------------------------------------------------
  DATA_EN     <=    '0';
  DATA_WREN   <=    '0';
  CODE_EN     <=    '0';
  IN_REQ      <=    '0';
  OUT_WREN    <=    '0';
  mux_select  <=   "00";
  pc_inc      <=    '0';
  pc_dec      <=    '0';
  cnt_inc     <=    '0';
  cnt_dec     <=    '0';
  ptr_inc     <=    '0';
  ptr_dec     <=    '0';

  case(fsm_state) is

    --when s_fsm_load =>  fsm_next_state  <=  s_fetch;

    when s_fetch  =>
      CODE_EN <= '1';
      fsm_next_state <= s_decode;
-------------------------------------------decode-----------------------------------------------------
    when s_decode =>
      case (CODE_DATA) is
        when X"3E"    => fsm_next_state <=  s_ptr_inc;
        when X"3C"    => fsm_next_state <=  s_ptr_dec;
        when X"2B"    => fsm_next_state <=  s_data_inc_0;
        when X"2D"    => fsm_next_state <=  s_data_dec_0;
        when X"2E"    => fsm_next_state <=  s_dis_out_0;
        when X"2C"    => fsm_next_state <=  s_dis_in_0;
        when X"5B"    => fsm_next_state <=  s_l_loop_0;
		    when X"5D"    => fsm_next_state <=  s_r_loop_0;
        when X"7E"    => fsm_next_state <=  s_break_0;
        when X"00"    => fsm_next_state <=  s_prog_stop;
        when others   => fsm_next_state <=  s_wait;

      end case ;
-------------------------------------------ptr_inc-----------------------------------------------------
    when s_ptr_inc =>
      ptr_inc <= '1';
      pc_inc <= '1';
      fsm_next_state <= s_fetch;
-------------------------------------------ptr_dec-----------------------------------------------------
    when s_ptr_dec =>
      ptr_dec <= '1';
      pc_inc <= '1';
      fsm_next_state <= s_fetch;
-------------------------------------------data_inc-----------------------------------------------------
    when s_data_inc_0 =>
      DATA_EN <= '1';
		  DATA_WREN <= '0';
      fsm_next_state <= s_data_inc_1;

    when s_data_inc_1 =>
      mux_select <= "01";
      fsm_next_state <= s_data_write_ram;
-------------------------------------------data_dec-----------------------------------------------------
    when s_data_dec_0 =>
      DATA_EN <= '1';
      DATA_WREN <= '0';
      fsm_next_state <= s_data_dec_1;

    when s_data_dec_1 =>
      mux_select <= "11";
      fsm_next_state <= s_data_write_ram;
--------------------------------------------------------------------------------------------------------
    when s_data_write_ram =>
      DATA_EN <= '1';
      DATA_WREN <= '1';
      pc_inc <= '1';
      fsm_next_state <= s_fetch;
--------------------------------------------------------------------------------------------------------
-------------------------------------------dis_out-----------------------------------------------------

    when s_dis_out_0 =>
      DATA_EN <= '1';
      DATA_WREN <= '0';
      fsm_next_state <= s_dis_out_1;

    when s_dis_out_1 =>
      if OUT_BUSY = '0' then
        OUT_WREN <= '1';
        pc_inc <= '1';
        fsm_next_state <= s_fetch;
      else
        DATA_EN <= '1';
        DATA_WREN <= '0';
        fsm_next_state <= s_dis_out_1;
      end if;
-------------------------------------------dis_in-----------------------------------------------------
    when s_dis_in_0 =>
      IN_REQ <= '1';
      mux_select <= "10";
      fsm_next_state <= s_dis_in_1;

    when s_dis_in_1 =>
      if IN_VLD = '1' then
        DATA_EN <= '1';
        DATA_WREN <= '1';
        pc_inc <= '1';
        fsm_next_state <= s_fetch;
      else
        IN_REQ <= '1';
        mux_select <= "10";
        fsm_next_state <= s_dis_in_1;
      end if;
-------------------------------------------l_loop-----------------------------------------------
    when s_l_loop_0 =>
      pc_inc <= '1';
      DATA_EN <= '1';
      DATA_WREN <= '0';
      fsm_next_state <= s_l_loop_1;

    when s_l_loop_1 =>
      if (DATA_RDATA = "00000000") then
        cnt_inc <= '1';
        CODE_EN <= '1';
        fsm_next_state <= s_l_loop_2;
      else
        fsm_next_state <= s_fetch;
      end if;

    when s_l_loop_2 =>
      if(cnt_reg = "000000000000")then
        fsm_next_state <= s_fetch;
      else
        if CODE_DATA = X"5B" then
          cnt_inc <= '1';
        elsif CODE_DATA = X"5D" then
          cnt_dec <= '1';
        end if;
        pc_inc <= '1';
        fsm_next_state <= s_l_loop_3;
      end if;
      
    when s_l_loop_3 =>
      CODE_EN <= '1';
      fsm_next_state <= s_l_loop_2;

-------------------------------------------r_loop---------------------------------  
    when s_r_loop_0 =>
      DATA_EN <= '1';
      DATA_WREN <= '0';
      fsm_next_state <= s_r_loop_1;
    
    when s_r_loop_1 =>
      if DATA_RDATA = "00000000" then 
        pc_inc <= '1';
        fsm_next_state <= s_fetch;
      else 
        cnt_inc <= '1';
        pc_dec <= '1';
        fsm_next_state <= s_r_loop_2;
      end if;
    
    when s_r_loop_2 =>
      CODE_EN <= '1';
      fsm_next_state <= s_r_loop_3;

    when s_r_loop_3 =>
      if cnt_reg = "000000000000" then
        fsm_next_state <= s_fetch; -- s_fetch
      else
        if CODE_DATA = X"5D" then
          cnt_inc <= '1';
        elsif CODE_DATA = X"5B" then
          cnt_dec <= '1';
        end if;
        fsm_next_state <= s_r_loop_4;
      end if;
    
    when s_r_loop_4 =>
      if  cnt_reg = "000000000000" then
        pc_inc <= '1';
        fsm_next_state <= s_fetch;
      else
        pc_dec <= '1';
        fsm_next_state <= s_r_loop_2;
      end if;
-------------------------------------------break--------------------------------- 

    when s_break_0 =>
      cnt_inc <= '1';
      pc_inc <= '1';
      fsm_next_state <= s_break_1;
    
    when s_break_1 =>
      CODE_EN <= '1';
      fsm_next_state <= s_break_2;

    when s_break_2 =>
      if cnt_reg = "000000000000" then
        fsm_next_state <= s_fetch;
      else
        if CODE_DATA = X"5D" then
          cnt_dec <= '1';
        elsif CODE_DATA = X"5B" then
          cnt_inc <= '1';
        end if;
        pc_inc <= '1';
        fsm_next_state <= s_break_1;
      end if;

-------------------------------------------stop-----------------------------------------------------
    when s_prog_stop => 
    fsm_next_state <= s_prog_stop;
-------------------------------------------wait-----------------------------------------------------
    when s_wait =>
      pc_inc <= '1';
      fsm_next_state <= s_fetch;
         
  end case ;


end process;
--FSM

end behavioral;



