/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     addons.c
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "addons.h"
#define led_d9 0x20 //0000|01
#define led_d10 0x10
#define led_d11 0x8
#define led_d12 0x4


void on_alarm(){
	RTC->IER |= RTC_IER_TAIE_MASK; //enable  alarm interrupt
	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_EnableIRQ(RTC_IRQn);
}

void off_alarm(){
	RTC->IER &= ~RTC_IER_TAIE_MASK; //disable  alarm interrupt
	NVIC_ClearPendingIRQ(RTC_IRQn);
	RTC->TAR = 0x0;
}

void delay(uint64_t time ){
    for(uint64_t i = 0; i < time; i++);
}


void beeep(){
	 for (uint32_t q=0; q<200; q++) {
		 PTA->PDOR |= GPIO_PDOR_PDO(0x10);
		 delay(300);
		 PTA->PDOR &= ~GPIO_PDOR_PDO(0x10);
		 delay(300);
	    }
}




void light2(){ //snake
		delay(1000000);
		PTB->PDOR &= ~led_d9;
		delay(500000);
		PTB->PDOR |= led_d11;

		delay(1000000);
		PTB->PDOR &= ~led_d10;
		delay(500000);
		PTB->PDOR |= led_d12;

		delay(1000000);
		PTB->PDOR &= ~led_d11;
		delay(500000);
		PTB->PDOR |= led_d9;

		delay(1000000);
		PTB->PDOR &= ~led_d12;
		delay(500000);
		PTB->PDOR |= led_d10;
}


void light3(){//flower
		PTB->PDOR &= ~led_d12;
		PTB->PDOR &= ~led_d9;
		delay(1000000/2);
		PTB->PDOR &= ~led_d10;
		PTB->PDOR &= ~led_d11;
		delay(1000000);
		PTB->PDOR |= led_d10;
		PTB->PDOR |= led_d11;
		delay(1000000/2);
		PTB->PDOR |= led_d12;
		PTB->PDOR |= led_d9;
		delay(1000000);

}


void light1(){
		PTB->PDOR &= ~led_d12;
		PTB->PDOR &= ~led_d9;
		PTB->PDOR &= ~led_d10;
		PTB->PDOR &= ~led_d11;
		delay(1000000);
		PTB->PDOR |= led_d12;
		PTB->PDOR |= led_d9;
		delay(1000000);
		PTB->PDOR |= led_d10;
		PTB->PDOR |= led_d11;
		delay(1000000);
}

void all_off(){
	PTB->PDOR |= led_d9;
	PTB->PDOR |= led_d10;
	PTB->PDOR |= led_d11;
	PTB->PDOR |= led_d12;
	PTA->PDOR |= GPIO_PDOR_PDO(0x10);
}



void ringtone1(){
	beeep();
	delay(1000000/4);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/4);
	beeep();

}

void ringtone2(){
	beeep();
	delay(1000000);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/4);
	beeep();
	delay(1000000/8);
	beeep();
	delay(1000000/10);
	beeep();
	delay(1000000/10);
	beeep();
	delay(1000000/8);
	beeep();
	delay(1000000/4);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000);



}

void ringtone3(){

	beeep();
	delay(1000000);
	beeep();
	delay(1000000);
	beeep();
	delay(1000000);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/3);
	beeep();
	delay(1000000);
	beeep();
	delay(1000000/2);
	beeep();
	delay(1000000/3);
	beeep();
	delay(1000000);;

}


void alert(uint8_t choose_lihgt, uint8_t choose_music){
	switch(choose_lihgt){
		case(1):
			light1();
			break;
		case(2):
			light2();
			break;
		case(3):
			light3();
			break;
		default:
			light1();
			break;

	}
	switch(choose_music){
			case(1):
				ringtone1();
				break;
			case(2):
				ringtone2();
				break;
			case(3):
				ringtone3();
				break;
			default:
				ringtone1();
				break;

		}
}

