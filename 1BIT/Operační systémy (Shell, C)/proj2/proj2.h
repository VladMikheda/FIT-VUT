/*
 * File:     proj2.h
 * Subject:  IOS 2021
 * Author:   Vladislav Mikheda
 * Login:    xmikhe00
 * Project:  "IOS – projekt 2 (synchronizace), Santa Claus problem"
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <semaphore.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>

// Semaphores name
#define SEMAFOR_NAME_1 "/xmikhe00_sem1"
#define SEMAFOR_NAME_2 "/xmikhe00_sem2"
#define SEMAFOR_NAME_3 "/xmikhe00_sem3"
#define SEMAFOR_NAME_4 "/xmikhe00_sem4"
#define SEMAFOR_NAME_5 "/xmikhe00_sem5"
#define SEMAFOR_NAME_6 "/xmikhe00_sem6"
#define SEMAFOR_NAME_7 "/xmikhe00_sem7"
#define SEMAFOR_NAME_8 "/xmikhe00_sem8"
#define SEMAFOR_NAME_9 "/xmikhe00_sem9"


#define ERROR -1

// Structure for arguments
typedef struct
{
    int NE;
    int NR;
    int TE;
    int TR;

}t_arguments;

// Structure for process shared
typedef struct
{
    int elves_exist;
    int elves_waiting;
    int deer_exist;
    int deer_waiting;
    long int line_counter;
    bool christmas_started;
    bool error;
}t_memery;

// Const
const int MAX_QUANTLY_ARGUMENTS = 5;
const int MAX_VALUE_NE_TE_RE = 1000;
const int MAX_VALUE_NR = 20;
const int MIN_VALUE_NE_NR_TE_RE = 0;
const int NUMBER_NE_ARG = 1;
const int NUMBER_NR_ARG = 2;
const int NUMBER_TE_ARG = 3;
const int NUMBER_TR_ARG = 4;
const int SECOND_TO_MICROSECOND = 1000;

// Function prototypes
t_arguments cheking_entered(int argc, char **argv);
void semafors_creating();
t_memery *create_sharing_memery(size_t size);
void destruction_sharing_memery();
void file_open();
void  file_close();
int my_random_elf(int m_time, int num);
void semaphores_unlink();
void semaphores_destruction();
void start_all();
void closing_all();
void santa_sleep();
void close_workshop();
void help_elves();
void christmas_start();
void santa_life(t_arguments* arguments);
void elves_start(int elf_number);
void elves_work(int elf_number,t_arguments *arguments);
void elves_get_helps(int elf_number);
void elves_taking_holidays(int elf_number);
void elves_life(t_arguments* arguments);
void deer_starts(int deer_number);
void deer_return_home(int deer_number, t_arguments *arguments);
void deer_life(t_arguments* arguments);

