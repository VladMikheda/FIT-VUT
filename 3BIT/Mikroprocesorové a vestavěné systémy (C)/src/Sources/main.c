/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     main.c
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "MK60D10.h"
#include "init.h"
#include "uart.h"
#include "times.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define _XOPEN_SOURCE


#define TIMEBUFFER 17
#define ALARMBUFFER 6
#define TIMEALERT 1
#define ISFR_MASK_RB 0x400
#define ISFR_MASK_UB 0x4000000
#define ISFR_MASK_DB 0x1000
#define ISFR_MASK_LB 0x8000000
#define ISFR_MASK_SW6 0x800
typedef enum e_state_FSM{
		START = 0,
	    SET_TIME,
	    SET_LIGHT,
	    SET_MUSIC,
	    SET_AMOUNT_REPEAT,
		SET_TIME_REPEAT,
	    SET_ALARM,
		ALARM,
		SLEEP
}state_FSM ;


state_FSM state = START;
uint8_t amount_repeat = 0;
int repeat_time = 0;
uint8_t amount_repeat_save = 0;
int repeat_time_save = 0;
uint8_t sleep_mode = 1;
uint32_t time_alert = TIMEALERT;
uint8_t alert_on = 0;
uint8_t alarm_sound = 1;
uint8_t alarm_light = 1;
uint8_t alarm_set = 0;
uint8_t alarm_time_set = 0;
char alarm_time[ALARMBUFFER];


void clean_alarm(){
	alarm_time_set = 0;
	for(int i = 0; i < ALARMBUFFER; i++){
		alarm_time[i] = '\0';
	}
}


void PORTE_IRQHandler(void){
	//look time
	if(PORTE->ISFR&ISFR_MASK_RB){
		if(alert_on == 0){
			char time_string_clock [TIMESTRING];
			time_t time_second = (time_t) RTC->TSR;
			return_time_stirng(time_second, time_string_clock);
			send_message("\r\nTime now:");
			send_message(time_string_clock);
			send_message("\r\n");

			if(alarm_set == 1){
				char time_string_alarm [TIMESTRING];
				time_second = (time_t) RTC->TAR;
				return_time_stirng(time_second, time_string_alarm);
				send_message("\r\nTime alarm:");
				send_message(time_string_alarm);
				send_message("\r\n");
			}
		}
		PORTE->ISFR = PORTE->ISFR;
	}

	// set all new
	if(PORTE->ISFR&ISFR_MASK_UB){
		if(alert_on == 0){
			off_alarm();

			state = SET_TIME;
			sleep_mode = 0;
			amount_repeat = 0;
			repeat_time = 0;
			time_alert = 0;
			alarm_set = 0;
			amount_repeat_save = 0;
			repeat_time_save = 0;

			clean_alarm();

			RTC->SR &= ~RTC_SR_TCE_MASK;
			RTC->TSR = 0x0;
			RTC->SR |= RTC_SR_TCE_MASK;
		}
		PORTE->ISFR = PORTE->ISFR;

	}

	//set new alarm
	if(PORTE->ISFR&ISFR_MASK_DB){
		if(alert_on == 0){
			off_alarm();

			sleep_mode = 0;
			amount_repeat = 0;
			repeat_time = 0;
			time_alert = 0;
			alarm_set = 0;
			amount_repeat_save = 0;
			repeat_time_save = 0;

			clean_alarm();

			state = SET_LIGHT;
		}
		PORTE->ISFR = PORTE->ISFR;

	}
	//repeat
	if(PORTE->ISFR&ISFR_MASK_LB){
		if(alert_on == 1){
			time_alert = 0;

			if(amount_repeat == 0){
				send_message("\r\nThe number of repetitions is 0 \r\n");
				send_message("\r\nAlarm clock off \r\n");

				amount_repeat = 0;
				repeat_time = 0;
				alarm_set = 0;

			}else{
				RTC->TAR = RTC->TSR;
				RTC->TAR += repeat_time;
				on_alarm();
				amount_repeat--;
				send_message("\r\nRepeat included\r\n");
			}

		}
		PORTE->ISFR = PORTE->ISFR;
	}
	//off/on alarm
	if(PORTE->ISFR&ISFR_MASK_SW6){
		if(alarm_set == 1){
			amount_repeat = 0;
			repeat_time = 0;
			time_alert = 0;
			alarm_set = 0;
			send_message("\r\nThe alarm clock and all its repetitions are stopped\r\n");
		}else{
			if(alarm_time_set == 1){
				int error = 0;

				uint32_t time_second = return_alarm_seconds(alarm_time, &error);


				RTC->TAR = time_second;
				time_alert = TIMEALERT;
				on_alarm();

				amount_repeat = amount_repeat_save;
				repeat_time = repeat_time_save;

				send_message("Alarm clock set\r\n");
				alarm_set = 1;
			}
		}
		PORTE->ISFR = PORTE->ISFR;

	}

}

void RTC_IRQHandler(void){
	if(RTC->SR&0x4){ //TAF
		state = ALARM;
		sleep_mode = 0;
		time_alert = TIMEALERT;
		RTC->TAR = RTC->TAR;
		off_alarm();
	}
}

void set_time(){

	char time[TIMEBUFFER];
	char choose = '\0';

	send_message("\r\nSet the time in the format dd-mm-YYYY HH:MM, minimum year 2022 maximum year 2037\r\n");
	send_message("Punctuation marks are placed automatically\r\n");
	send_message("Set: ");
	recive_time(time);

	send_message("You set the time:");
	send_message(time);
	send_message("\r\n\r\nConfirm: 1 -> Yes, Other -> No\r\n");
	recive_choice(&choose);
	send_message("\r\n");

	if(choose == '1'){
		int error = 0;
		int time_second = return_seconds(time, &error);

		if(error){
			state = SET_TIME;
			return;
		}

		//set time for RTC
		RTC->SR &= ~RTC_SR_TCE_MASK;
		RTC->TSR = time_second;
		RTC->SR |= RTC_SR_TCE_MASK;


		state = SET_LIGHT;
		choose = '\0';
		send_message("\r\nSet an alarm or put the system to sleep mode: 1 -> Alarm, Other -> Sleep Mode\r\n");
		send_message("Set: ");
		recive_choice(&choose);
		send_message("\r\n");

		if(choose != '1'){
			state = SLEEP;
			return;
		}

	}else{
		state = SET_TIME;
	}


}

void set_amount_repeat(){


	amount_repeat = 0;
	repeat_time = 0;

	int error = 0;

	send_message("\r\nSet the number of times the alarm will repeat, 00 - 10 in NN format\r\n");
	send_message("Set: ");
	int amount = recive_amount_repeat(&error);
	send_message("\r\n");

	if(error){
		send_message("ERROR: the specified number does not match the requirement\r\n");
		state = SET_AMOUNT_REPEAT;
		return;
	}

	amount_repeat = (uint8_t) amount;
	amount_repeat_save = amount_repeat;

	if(amount_repeat == 0){
		repeat_time_save = 0;

		state = SET_ALARM;
		return;
	}

	state = SET_TIME_REPEAT;
}


void set_time_repeat(){
	int error = 0;

	send_message("\r\nSpecify the amount of time between repetitions, time is set in minutes 01 - 60 in NN format\r\n");
	send_message("Set: ");
	int time = recive_time_repeat(&error);
	send_message("\r\n");

	if(error){
		send_message("ERROR: the specified number does not match the requirement\r\n");
		state = SET_TIME_REPEAT;
		return;
	}

	repeat_time = time * 60;
	repeat_time_save = repeat_time;

	send_message("\r\nGo to set alarm time or change repetitions: 1 -> Alarm, Other -> Repeat\r\n");
	char choose = '\0';
	recive_choice(&choose);
	send_message("\r\n");
	if(choose != '1'){
		state = SET_AMOUNT_REPEAT;
		return;
	}

	state = SET_ALARM;
}


void set_alarm(){

	clean_alarm();
	char choose = '\0';
	send_message("\r\nSet the time for alarm in the format HH:MM\r\n");
//	send_message("Punctuation marks are placed automatically\r\n");
	send_message("Set: ");
	recive_alarm_time(alarm_time); // &

	send_message("You set the time:");
	send_message(alarm_time);
	send_message("\r\n\r\nConfirm: 1 -> Yes, Other -> No\r\n");
	recive_choice(&choose);
	send_message("\r\n");

	if(choose == '1'){
		int error = 0;
		uint32_t time_second = return_alarm_seconds(alarm_time, &error);

		if(error){
			state = SET_ALARM;
			return;
		}

		RTC->TAR = time_second;
		time_alert = TIMEALERT;
		on_alarm();
		alarm_time_set = 1;

		send_message("Alarm clock set\r\n");
		alarm_set = 1;

		state = SLEEP;

	}else{
		state = SET_ALARM;
	}
}


void set_light(){
	char choose = '\0';
	send_message("\r\nChoose from three highlights when the alarm rings 1 or 2 or 3:\r\n");
	send_message("Set: ");
	recive_choice(&choose);
	send_message("\r\n");
	if(choose == '1'){
		alarm_light = 1;
	}else if(choose == '2'){
		alarm_light = 2;
	}else if(choose == '3'){
		alarm_light = 3;
	}else{
		send_message("No choice, please try again\r\n");
		state = SET_LIGHT;
		return;
	}

	state = SET_MUSIC;
}



void set_music(){
	char choose = '\0';
	send_message("\r\nChoose one of the alarm ringtones 1 or 2 or 3:\r\n");
	send_message("Set: ");
	recive_choice(&choose);
	send_message("\r\n");
	if(choose == '1'){
		alarm_sound = 1;
	}else if(choose == '2'){
		alarm_sound = 2;
	}else if(choose == '3'){
		alarm_sound = 3;
	}else{
		send_message("No choice, please try again\r\n");
		state = SET_MUSIC;
		return;
	}

	state = SET_AMOUNT_REPEAT;
}


void alarm(){
	alert_on = 1;
	while(time_alert){
		alert(alarm_light, alarm_sound);
	}
	all_off();
	alert_on = 0;
	state = SLEEP;
}


int main(void)
{
	init();

	while(1){
		switch(state){
			case(START):
				send_message("IMP 2022 project\r\n");
				send_message("Author Vladislav Mikheda\r\n");
				state = SET_TIME;
				break;
			case(SET_TIME):
				set_time();
				break;
			case(SET_LIGHT):
				set_light();
				break;
			case(SET_MUSIC):
				set_music();
				break;
			case(SET_AMOUNT_REPEAT):
				set_amount_repeat();
				break;
			case(SET_TIME_REPEAT):
				set_time_repeat();
				break;
			case(SET_ALARM):
				set_alarm();
				break;
			case(ALARM):
				alarm();
				break;
			case(SLEEP):
				sleep_mode = 1;
				send_message("\r\nThe system goes into sleep mode to exit the mode, use the buttons:\r\n");
				send_message("Button up set the clock and alarm\r\n");
				send_message("Down button alarm setting\r\n");
				send_message("Right button display time\r\n");
				while(sleep_mode);
				break;




		}
	}


    return 0;
}

