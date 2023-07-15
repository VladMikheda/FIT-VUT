/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     uart.c
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "uart.h"
#include "MK60D10.h"

void send_char(char ch)  {
    while(!(UART5->S1 & UART_S1_TDRE_MASK) && !(UART5->S1 & UART_S1_TC_MASK) );
    UART5->D = ch;
}

void send_message(char *s)  {

    int i = 0;
    while (s[i]!=0){
        send_char(s[i++]);
    }
}


char recive_char(){
	while(!(UART5->S1 & UART_S1_RDRF_MASK));
	return UART5->D;
}



void recive_time(char *buffer_time){
	int counter = 0;
	int max_count = 16;
	while(counter < max_count){
		char c = recive_char();

		send_char(c);
		buffer_time[counter] = c;

		if(counter == 1 || counter == 4){
			send_char('-');
			counter++;
			buffer_time[counter] = '-';
		}else if(counter == 9){
			send_char(' ');
			counter++;
			buffer_time[counter] = ' ';
		}else if(counter == 12){
			send_char(':');
			counter++;
			buffer_time[counter] = ':';
		}else if(counter == 15){
			send_message("\r\n");
			counter++;
			buffer_time[counter] = '\0';
		}

		counter ++;

	}
}



void recive_alarm_time(char *buffer_time){
	int counter = 0;
	int max_count = 6;
	while(counter < max_count){
		char c = recive_char();

		send_char(c);
		buffer_time[counter] = c;

		if(counter == 1){
			send_char(':');
			counter++;
			buffer_time[counter] = ':';
		}else if(counter == 4){
			send_message("\r\n");
			counter++;
			buffer_time[counter] = '\0';
		}

		counter ++;

	}
}





void recive_choice(char *choice){
	char c = recive_char();
	send_char(c);
	*choice = c;
}


int recive_amount_repeat(int *error){
	char number[MAXREPEATCHAR];
	for(int i = 0; i < MAXREPEATCHAR;i++){
		char c = recive_char();
		send_char(c);
		number[i] = c;
	}

	if(number[0] == '0' && number[1] == '0'){
		*error = 0;
		return 0;
	}

	int n = atoi(number);

	if(n < 1|| n > MAXAMOUNTREPEAT){
		*error = 1;
	}else{
		*error = 0;
		return n;
	}

	return 0;

}


int recive_time_repeat(int *error){
	char time[MAXTIMEREPATCHAR];
	for(int i = 0; i < MAXTIMEREPATCHAR;i++){
		char c = recive_char();
		send_char(c);
		time[i] = c;
	}


	int n = atoi(time);

	if(n < 1|| n > MAXTIMEREPEAT){
		*error = 1;
	}else{
		*error = 0;
		return n;
	}

	return 0;

}



