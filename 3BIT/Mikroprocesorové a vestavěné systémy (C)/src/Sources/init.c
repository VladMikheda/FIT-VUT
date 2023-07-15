/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     init.c
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "init.h"
void uart_init(){

    UART5->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK); // disable  transmitter and receiver

    //8-bit mode no par
    UART5->C1 = 0x00;

    UART5->BDH = 0x00;
    UART5->BDL = 0x1A; //The baud rate 115200Bd
    UART5->C4 = 0x0F;
    UART5->C3 = 0x00;
    UART5->MA1 = 0x00;
    UART5->MA2 = 0x00;

    UART5->S2 |= 0xC0;
    UART5->C2 |= ( UART_C2_TE_MASK | UART_C2_RE_MASK );	// enable transmitter and receiver

}

void rtc_init(){

    RTC->CR |= RTC_CR_SWR_MASK; //enable reset all RTC registers
    RTC->CR &= ~RTC_CR_SWR_MASK; //desable reset RTC


    RTC->CR |= RTC_CR_OSCE_MASK;
    delay(0x3E8);

    RTC->TSR = 0x0; //set start value for RTC


    RTC->SR |= RTC_SR_TCE_MASK; //start RTC

}

void port_init(){

    //UART5
    PORTE->PCR[8] = PORT_PCR_MUX(0x03);
    PORTE->PCR[9] = PORT_PCR_MUX(0x03);

    // Led
    PORTB->PCR[5] = PORT_PCR_MUX(0x01); // D9
    PORTB->PCR[4] = PORT_PCR_MUX(0x01); // D10
    PORTB->PCR[3] = PORT_PCR_MUX(0x01); // D11
    PORTB->PCR[2] = PORT_PCR_MUX(0x01); // D12

    //buttom
    PORTE->PCR[10] =( PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A)
					| PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01)
					| PORT_PCR_PS(0x01)); // look time
    PORTE->PCR[26] =( PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A)
    				| PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01)
    				| PORT_PCR_PS(0x01)); // new set all
    PORTE->PCR[27] =( PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A)
        			| PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01)
        			| PORT_PCR_PS(0x01)); // repeat
    PORTE->PCR[12] =( PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A)
           			| PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01)
           			| PORT_PCR_PS(0x01)); // new set alarm

    PORTE->PCR[11] =( PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A)
           			| PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01)
           			| PORT_PCR_PS(0x01)); // off alarm

    NVIC_ClearPendingIRQ(PORTE_IRQn);
    NVIC_EnableIRQ(PORTE_IRQn);

    //beep
    PORTA->PCR[4] = PORT_PCR_MUX(0x01);



    PTA->PDDR = GPIO_PDDR_PDD(0x10);
    PTA->PDOR |= GPIO_PDOR_PDO(0x10);


    PTB->PDDR = GPIO_PDDR_PDD(0x3C); // set outputs LEDs
    PTB->PDOR |= GPIO_PDOR_PDO( 0x3C); //set 0 to outputs


}


void system_init(){

    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK; //watchdog disable
    SIM_CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(0x00); //delimetr 0
    MCG_C4 |= ( MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x01)); //32

    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTA_MASK;
    SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;

}


void init(){
    system_init();
    port_init();
    uart_init();
    rtc_init();
}
