/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     uart.h
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#define MAXTIMEREPEAT 60
#define MAXAMOUNTREPEAT 10

#define MAXREPEATCHAR 2
#define MAXTIMEREPATCHAR 2
void send_message(char *s);
void recive_time(char *buffer_time);
void recive_choice(char *choice);
int recive_amount_repeat(int *error);
int recive_time_repeat(int *error);
void recive_alarm_time(char *buffer_time);
