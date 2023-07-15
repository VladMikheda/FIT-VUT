/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     time.h
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#include <time.h>
#define TIMESTRING 20

void return_time_stirng(time_t seconds, char* time_string);
time_t return_seconds(char *inpute_time, int *error);
time_t return_alarm_seconds(char *inpute_time, int *error);
