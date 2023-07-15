/**
 * Project: Hodiny s budikem na bazi modulu Real Time Clock (RTC)
 *
 * File:     addons.h
 * Subject:  IMP 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "MK60D10.h"
void on_alarm();
void off_alarm();
void delay(uint64_t time);
void beeep();
void alert(uint8_t choose_lihgt, uint8_t choose_music);
void light2();
void all_off();
void ringtone2();
//void ringtone1();
//void ringtone2();
//void ringtone3();
