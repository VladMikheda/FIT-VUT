/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     time.c
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#include "MK60D10.h"
#include "times.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#define _XOPEN_SOURCE


time_t return_seconds(char *inpute_time, int *error){
	struct tm s_time;
	memset(&s_time, 0, sizeof(s_time));
	if(!(strptime(inpute_time, "%d-%m-%Y %H:%M", &s_time))){
		*error = 1;
		send_message("ERROR: date format not correct");
		return 0;
	}

	if(s_time.tm_min < 0 || s_time.tm_min > 59){
		*error = 1;
		send_message("\r\nERROR: minutes must be specified as a number between 0 and 59");
	}

	if(s_time.tm_hour < 0 || s_time.tm_hour > 23){
		*error = 1;
		send_message("\r\nERROR: hours must be specified as a number between 0 and 23");
	}

	if(s_time.tm_mday < 1 || s_time.tm_mday > 31 ){
		*error = 1;
		send_message("\r\nERROR: day must be specified as a number between 1 and 31");
	}

	if(s_time.tm_mon < 0 || s_time.tm_mon > 11){
		*error = 1;
		send_message("\r\nERROR: month must be specified as a number between 1 and 12");
	}

	if(s_time.tm_year+1900 < 2022 || s_time.tm_year+1900 > 2037){
		*error = 1;
		send_message("\r\nERROR: year must be given as a number between 2022 and 2037");
	}
	if(*error == 1){
		send_message("\r\n");
		return 0;
	}

	time_t time_second = mktime(&s_time);
	return time_second;
}

void return_time_stirng(time_t seconds, char* time_string){
	struct tm s_time;
	memset(&s_time, 0, sizeof(s_time));
	localtime_r(&seconds, &s_time);
	strftime(time_string, TIMESTRING, "%d-%m-%Y %H:%M:%S", &s_time);
}


void return_time_structure(struct tm *clock_time){
	time_t seconds = (time_t) RTC->TSR;
	memset(clock_time, 0, sizeof(*clock_time));
	localtime_r(&seconds, clock_time);
}


time_t return_alarm_seconds(char *inpute_time, int *error){

	struct tm alarm_time;
	struct tm clock_time;

	memset(&alarm_time, 0, sizeof(alarm_time));
	if(!(strptime(inpute_time, "%H:%M", &alarm_time))){
		*error = 1;
		send_message("ERROR: date format not correct");
		return 0;
	}


	if(alarm_time.tm_min < 0 || alarm_time.tm_min > 59){
			*error = 1;
			send_message("\r\nERROR: minutes must be specified as a number between 0 and 59");
		}

	if(alarm_time.tm_hour < 0 || alarm_time.tm_hour > 23){
		*error = 1;
		send_message("\r\nERROR: hours must be specified as a number between 0 and 23");
	}
	if(*error == 1){
			send_message("\r\n");
			return 0;
		}


	return_time_structure(&clock_time);

	clock_time.tm_mon = 0;
	clock_time.tm_year = 70;
	clock_time.tm_mday = 1;
	clock_time.tm_wday = 0;
	clock_time.tm_yday = 0;
	time_t second_clock_begin_day = mktime(&clock_time);

	time_t second_alarm_begin_day = 0;

	if(clock_time.tm_hour < alarm_time.tm_hour || ((clock_time.tm_hour == alarm_time.tm_hour) && (clock_time.tm_min < alarm_time.tm_min))){

		alarm_time.tm_mon = 0;
		alarm_time.tm_year = 70;
		alarm_time.tm_mday = 1;
		second_alarm_begin_day = mktime(&alarm_time);

	}else{
		// clock_time.tm_hour >  alarm_time.tm_hour

		alarm_time.tm_mon = 0;
		alarm_time.tm_year = 70;
		alarm_time.tm_mday = 2;
		clock_time.tm_yday = 1;
		second_alarm_begin_day = mktime(&alarm_time);
	}


	time_t second_now = RTC->TSR;

	time_t alarm_second = (second_now - second_clock_begin_day) + second_alarm_begin_day;
	return alarm_second;
//	RTC->TAR = alarm_time;
}


