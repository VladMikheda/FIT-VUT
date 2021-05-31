/*
 * File:     proj2.c
 * Subject:  IOS 2021
 * Author:   Vladislav Mikheda
 * Login:    xmikhe00
 * Project:  "IOS – projekt 2 (synchronizace), Santa Claus problem"
 */

#include "proj2.h"

//semaphores
sem_t *s_help_elves = NULL;
sem_t *s_line_block = NULL;
sem_t *s_bed_block= NULL;
sem_t *s_elves_block = NULL;
sem_t *s_num_block = NULL;
sem_t *s_christmas_block = NULL;
sem_t *s_end_block = NULL;
sem_t *s_santa_block = NULL;
sem_t *s_harness_block = NULL;

//shared memory
t_memery * quantity=NULL;

//output file
FILE *file_out;

/*
 * Function checks incoming arguments
 * In case of incorrect input, it issues an error and terminates the program
 * With correct structure with arguments
 */
t_arguments cheking_entered(int argc, char **argv)
{

    if(argc != MAX_QUANTLY_ARGUMENTS)
    {
        fprintf(stderr, "ERROR:Invalid number of arguments specified\n");
        exit(ERROR);
    }
    if(!(MIN_VALUE_NE_NR_TE_RE < atoi(argv[NUMBER_NE_ARG]) && atoi(argv[NUMBER_NE_ARG]) < MAX_VALUE_NE_TE_RE))
    {
        fprintf(stderr, "ERROR:The number of elves must be in the range 0 < NE <1000\n");
        exit(ERROR);
    }

    if(!(MIN_VALUE_NE_NR_TE_RE < atoi(argv[NUMBER_NR_ARG]) && atoi(argv[NUMBER_NR_ARG]) < MAX_VALUE_NR))
    {
        fprintf(stderr, "ERROR:The number of reindeer must be in the range 0 < NR < 20\n");
        exit(ERROR);
    }
    if(!(MIN_VALUE_NE_NR_TE_RE <= atoi(argv[NUMBER_TE_ARG]) && atoi(argv[NUMBER_TE_ARG]) <= MAX_VALUE_NE_TE_RE))
    {
        fprintf(stderr, "ERROR:Waiting for elves must be in range 0 <= TE <= 1000\n");
        exit(ERROR);
    }
    if(!(MIN_VALUE_NE_NR_TE_RE <= atoi(argv[NUMBER_TR_ARG]) && atoi(argv[NUMBER_TR_ARG]) <= MAX_VALUE_NE_TE_RE))
    {
        fprintf(stderr, "ERROR:Waiting for deer must be in range 0 <= TE <= 1000\n");
        exit(ERROR);
    }

    //
    t_arguments arguments;
    arguments.NE = atoi(argv[NUMBER_NE_ARG]);
    arguments.NR = atoi(argv[NUMBER_NR_ARG]);
    arguments.TE = atoi(argv[NUMBER_TE_ARG]);
    arguments.TR = atoi(argv[NUMBER_TR_ARG]);


    return arguments;
} //arguments


/*
 * The function creates semaphores
 */
void semafors_creating()
{
    sem_unlink(SEMAFOR_NAME_1);
    sem_unlink(SEMAFOR_NAME_2);
    sem_unlink(SEMAFOR_NAME_3);
    sem_unlink(SEMAFOR_NAME_4);
    sem_unlink(SEMAFOR_NAME_5);
    sem_unlink(SEMAFOR_NAME_6);
    sem_unlink(SEMAFOR_NAME_7);
    sem_unlink(SEMAFOR_NAME_8);
    sem_unlink(SEMAFOR_NAME_9);


    if((s_help_elves = sem_open(SEMAFOR_NAME_1,O_CREAT | O_EXCL, 0666, 0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_line_block = sem_open(SEMAFOR_NAME_2, O_CREAT | O_EXCL, 0666,1)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_bed_block = sem_open(SEMAFOR_NAME_3, O_CREAT | O_EXCL, 0666,0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_num_block = sem_open(SEMAFOR_NAME_4,O_CREAT | O_EXCL, 0666,1)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_elves_block = sem_open(SEMAFOR_NAME_5,O_CREAT | O_EXCL, 0666,1)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_christmas_block = sem_open(SEMAFOR_NAME_6,O_CREAT | O_EXCL, 0666,0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_end_block = sem_open(SEMAFOR_NAME_7,O_CREAT | O_EXCL, 0666,0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_santa_block = sem_open(SEMAFOR_NAME_8,O_CREAT | O_EXCL, 0666,0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
    if((s_harness_block = sem_open(SEMAFOR_NAME_9,O_CREAT | O_EXCL, 0666,0)) == SEM_FAILED)
    {
        fprintf(stderr,"ERROR:Semaphore could not be created");
        exit(ERROR);
    }
}

/*
 * The function creates shared memory
 */
t_memery *create_sharing_memery(size_t size)
{
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,-1,0);
}

/*
 * The function destructions shared memory
 */
void destruction_sharing_memery()
{
    if((munmap(quantity, sizeof(t_memery))) == ERROR)
    {
        fprintf(stderr,"ERROR:Unable to clear shared memory");
        exit(ERROR);
    }
}

/*
 *The function opens a file for output
 */
void file_open()
{
   if((file_out = fopen("proj2.out","w")) == NULL)
   {
       fprintf(stderr,"ERROR:File open error");
       exit(ERROR);
   }

}

/*
 * The function closes the file for output
 */
void  file_close()
{
    if((fclose(file_out)) == EOF)
    {
        fprintf(stderr,"ERROR:File close error");
        exit(ERROR);
    }
}

/*
 * A function that generate a random number from 0 to a given number
 * Returns a number in microseconds(*1000)
 */
int my_random_elf(int m_time, int num)
{
    srand((time(NULL) + rand() ) * num);

    if(m_time == 0) //If given 0 returns zero
        return 0;  //To prevent division by 0

    return (rand() % m_time) * SECOND_TO_MICROSECOND;
}

/*
 * A function that generate a random number from a given number/2 to a given number
 * Returns a number in microseconds(*1000)
 */
int my_random_deer(int m_time, int num)
{
    srand((time(NULL) + rand() ) * num);

    if(m_time == 0)     //If given 0 returns zero
    {                  //To prevent division by 0
        return 0;
    } else if (m_time == 1)
    {
        if((rand() % 1) > 0.5)                  //If given 1 returns zero or one
            return 1 * SECOND_TO_MICROSECOND;   //To prevent division by 0
        else
            return 0;
    }
    return ((m_time/2) + rand() % (m_time/2)) * SECOND_TO_MICROSECOND;
}


/*
 * The function unlinks semaphores
 */
void semaphores_unlink()
{
    if (sem_unlink(SEMAFOR_NAME_1) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_2) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_3) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_4) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_5) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_6) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_7) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_8) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
    if (sem_unlink(SEMAFOR_NAME_9) == ERROR )
    {
        fprintf(stderr,"ERROR:Failed unlink semaphore\n");
        exit(ERROR);
    }
}

/*
 * The function removes semaphores
 * Calls the function to unlink them
 */
void semaphores_destruction()
{
    if(sem_close(s_help_elves) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_line_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_bed_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_num_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_elves_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_christmas_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_end_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_santa_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }
    if(sem_close(s_harness_block) == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to close semaphore\n");
        exit(ERROR);
    }

    semaphores_unlink();
}

/*
 * The function is called before the process splits
 * The function is called functions of:
 *                          creating shared memory
 *                          creating semaphores
 *                          opening an output file
 *
 * Defines starting values for counters
 */
void start_all()
{
    quantity = create_sharing_memery(sizeof(t_memery));
    semafors_creating();
    file_open();
    quantity->christmas_started = false;
    quantity->line_counter = 0;
    quantity->elves_waiting = 0;
    quantity->elves_exist = 0;
    quantity->deer_exist = 0;
    quantity->deer_waiting=0;
    quantity->error = false;
}

/*
 *The function is called after the processes have finished
 *The function is called functions of:
 *                      destructions shared memory
 *                      semaphore destruction
 *                      сlosing the file
 */
void closing_all()
{
    destruction_sharing_memery();
    semaphores_destruction();
    file_close();
}

/*#############################*/
/*-----Star santa function-----*/
/*#############################*/

/*
 * The function is triggered when santa goes to sleep
 * Outputs to a file that Santa is sleeping
 */
void santa_sleep()
{
    sem_wait(s_line_block);// blocked output in file_out
    sem_wait(s_num_block); // shared memory change lock
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block); // Shared memory change unlock
    //printf("%ld: Santa: going to sleep\n", quantity->line_counter);
    fprintf(file_out,"%ld: Santa: going to sleep\n", quantity->line_counter);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);// unblocked output in file_out
}

/*
 * The function is triggered when santa closing workshop
 * Outputs to a file that Santa closed workshop
 * The semaphore responsible for splitting the file record is opened in the function santa_life
 *                                                       it is necessary so that the process cannot stop unexpectedly
 */
void close_workshop()
{
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Santa: closing workshop\n", quantity->line_counter);
    fprintf(file_out,"%ld: Santa: closing workshop\n", quantity->line_counter);//Critical section of writing to file
    fflush(file_out);
    quantity->christmas_started = true; //hangs up a sign that the store is closed
    sem_post(s_help_elves); //Unlock unobstructed passage for elves in the queue
    sem_post(s_line_block); // unblocked output in file_out
}

/*
 * The function is triggered when Santa helps the elves
 * Outputs to a file that Santa is helping elves
 */
void help_elves()
{
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Santa: helping elves\n", quantity->line_counter);
    fprintf(file_out,"%ld: Santa: helping elves\n", quantity->line_counter);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);
}

/*
 * The function is triggered when santa starts christmas
 * Outputs to a file that Santa started Christmas
 *
 * Semaphores are opened and closed in the deer_life function so that
 *                                                  the process cannot stop in an unplanned place
 */
void christmas_start()
{
    quantity->line_counter++;//Critical section for changing shared memory
    //printf("%ld: Santa: Christmas started\n", quantity->line_counter);
    fprintf(file_out,"%ld: Santa: Christmas started\n", quantity->line_counter);//Critical section of writing to file
    fflush(file_out);
}

/*
 * The main functional process of santa calls all other functions
 */
void santa_life(t_arguments* arguments)
{
    while(1)
    {
        // function Santa sleep //
        santa_sleep();

        sem_wait(s_bed_block); //semaphore blocks Santa before helping elves or harnessing reindeer
        sem_wait(s_line_block); // blocking output in file_out

        if(quantity->deer_waiting == arguments->NR) //if all the reindeer are back santa goes to help the reindeer
        {
            close_workshop();

            //santa harnessing deer
            for(int i = 1; i <= arguments->NR; i++)
                sem_post(s_harness_block);

            sem_wait(s_christmas_block);// santa is waiting deer
            christmas_start();// Santa stared Christmas
            sem_post(s_harness_block); //Unlock the semaphore to allow the last deer process to end
            sem_post(s_end_block); // Unlocked finished program
            exit(0); //Santa process to end
        }
        else if(quantity->elves_waiting == 3) // If at least 3 elves are waiting for help, Santa goes to help the elves
        {
            help_elves();
            sem_post(s_help_elves); //Unblocks the process for the elves to get help
            sem_wait(s_santa_block); //Santa is waiting when finished helping elves
        }
    }

}

/*#############################*/
/*-----Star elves function-----*/
/*#############################*/


/*
 * The function is triggered when elves stats process
 * Outputs to a file that Elf started
 */
void elves_start(int elf_number)
{
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Elf %d: started \n", quantity->line_counter, elf_number);
    fprintf(file_out,"%ld: Elf %d: started \n", quantity->line_counter, elf_number);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);
}

/*
 * The function is triggered when elves are working a after needs help
 * Outputs to a file that Elf need help
 */
void elves_work(int elf_number,t_arguments *arguments)
{
    usleep(my_random_elf(arguments->TE, elf_number));// Stopping the process for a while
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Elf %d: need help\n", quantity->line_counter, elf_number);
    fprintf(file_out,"%ld: Elf %d: need help\n", quantity->line_counter, elf_number);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);
}

/*
 * The function is triggered when santa helped the elves
 * Outputs to a file that Elf get help
 */
void elves_get_helps(int elf_number)
{
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Elf %d: get help \n", quantity->line_counter, elf_number);
    fprintf(file_out, "%ld: Elf %d: get help \n", quantity->line_counter, elf_number);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);
}

/*
 * The function is triggered when santa left to harness the reindeer and closed the workshop
 * Outputs to a file that Elf taking holidays
 */
void elves_taking_holidays(int elf_number)
{
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: Elf %d: taking holidays \n", quantity->line_counter, elf_number);
    fprintf(file_out, "%ld: Elf %d: taking holidays \n", quantity->line_counter, elf_number);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_elves_block);
    sem_post(s_help_elves);
    sem_post(s_line_block);
}

/*
 * The main functional process of elf calls all other functions
 */
void elves_life(t_arguments* arguments)
{
    for(int elf_number = 1; elf_number <= arguments->NE; elf_number++)
    {
        pid_t elf = fork();
        if(elf == 0)
        {
            // function elves_srated
            elves_start(elf_number);

            while(1)
            {
                // function elf_work
                elves_work(elf_number, arguments);


                // Function cekarna elfu
                /*
                 * The elves go to Santa in three, the first 2 elves enter, launching each other,
                 * and the 3rd elf, then the elves wait for the process of santa to wake up
                 * aif the process is closed the workshop one elf freely passes on
                 * and opens the way for the next
                 *
                 * The elf, leaving the function, reduces the counter, the last zlf from the
                 * trinity unlocks the santa process
                 */
                sem_wait(s_elves_block); //Entering the queue   (critical section)
                sem_wait(s_num_block);
                quantity->elves_waiting++;//Critical section for changing shared memory
                sem_post(s_num_block);

                if(quantity->elves_waiting == 3)
                    sem_post(s_bed_block);//The third elf unlocks the santa process because there are already 3 elves in the queue
                else
                {
                    sem_post(s_elves_block);//Unlocking the queue for the next two elves
                }
                sem_wait(s_help_elves);//Waiting for santa to unlock the semaphore

                if(!(quantity->christmas_started)) //If it's not closed workshop then get help
                {
                    elves_get_helps(elf_number);
                }
                else                               //If the workshop is closed, go taking holidays
                {
                    // function taking holidays
                    elves_taking_holidays(elf_number);

                    //Elves end their process the last elf unlocks the semaphore of the main final process
                    sem_wait(s_num_block);
                    quantity->elves_exist++; //Critical section for changing shared memory
                    if (quantity->elves_exist == arguments->NE) {
                        sem_post(s_end_block);
                    }
                    sem_post(s_num_block);//Unlocks the semaphore of the main final process
                    exit(0);
                    // Stop //
                }

                sem_post(s_help_elves);//Once help is received, one process paves the way for the next
                sem_wait(s_num_block);
                quantity->elves_waiting--;   //Critical section for changing shared memory
                if(quantity->elves_waiting == 0)
                {
                    if(!(quantity->christmas_started))       //If the workshop is not closed, then it closes the additional semaphore
                    {                                       //if the workshop is closed, then the semaphore does not close the elf
                        sem_wait(s_help_elves);            //for the unimpeded passage of the next process
                    }
                    sem_post(s_santa_block);     //The last of the elf trinity unlocks the santa process
                    sem_post(s_elves_block);    //Launches a new elf in line
                }
                sem_post(s_num_block);
            }
        }
        else if (elf < 0)
        {
            fprintf(stderr,"ERROR:Failed to create process elf\n");
            fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
            fprintf(stderr,"All records in the file proj2.out are not valid\n");
            quantity->error = true;
            for(int f = 0; f < 3; f++) // If the process has not been created, we allow the main process to close all the closures to terminate the program abnormally
            {
                sem_post(s_end_block);
            }
            exit(ERROR);

        }
    }
}

/*#############################*/
/*-----Star deer function-----*/
/*#############################*/

/*
 * The function is triggered when deer stats process
 * Outputs to a file that Deer rstarted
 */
void deer_starts(int deer_number)
{
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    sem_post(s_num_block);
    //printf("%ld: RD %d: rstarted \n", quantity->line_counter, deer_number);
    fprintf(file_out,"%ld: RD %d: rstarted \n", quantity->line_counter, deer_number);//Critical section of writing to file
    fflush(file_out);
    sem_post(s_line_block);
}

/*
 * The function is triggered when deer resting and returning from vacation
 * Outputs to a file that Deer return home
 */
void deer_return_home(int deer_number, t_arguments *arguments)
{
    usleep(my_random_deer(arguments->TR, deer_number));// Stopping the process for a while
    sem_wait(s_line_block);
    sem_wait(s_num_block);
    quantity->line_counter++;//Critical section for changing shared memory
    //printf("%ld: RD %d: return home\n", quantity->line_counter, deer_number);
    fprintf(file_out,"%ld: RD %d: return home\n", quantity->line_counter, deer_number);//Critical section of writing to file
    fflush(file_out);
    quantity->deer_waiting++;  //Critical section for changing shared memory

    if(quantity->deer_waiting == arguments->NR)
        sem_post(s_bed_block); //Unlocks the santa process when everyone is back from vacation

    sem_post(s_num_block);
    sem_post(s_line_block);
}

/*
 * The main functional process of deer calls all other functions
 */
void deer_life(t_arguments* arguments)
{
    for(int deer_number = 1; deer_number <= arguments->NR; deer_number++)
    {
        pid_t deer = fork();
        if(deer == 0)
        {
            // function deer started //
            deer_starts(deer_number);

            // function deer holidays //
            deer_return_home(deer_number, arguments);


            // function deer work //
            /*
             * Reindeer wait for Santa Claus to harness, then all but the last one
             * complete the process, the last reindeer completes its process before
             * Santa Claus process ends opening a semaphore for him
             */
            sem_wait(s_harness_block);//The process is blocked until Santa writes out what the store closes

            sem_wait(s_line_block);
            sem_wait(s_num_block);
            quantity->line_counter++;//Critical section for changing shared memory
            sem_post(s_num_block);
            //printf("%ld: RD %d: get hitched\n", quantity->line_counter, deer_number);
            fprintf(file_out,"%ld: RD %d: get hitched\n", quantity->line_counter, deer_number);//Critical section of writing to file
            fflush(file_out);
            sem_wait(s_num_block);
            quantity->deer_waiting--;//Critical section for changing shared memory
            if(quantity->deer_waiting == 0)    //If this is the last process deer
            {
                sem_post(s_christmas_block); //Opens semaphore santa
                sem_wait(s_harness_block); // Is blocked until the santa process is ready to terminate
                sem_post(s_end_block);  //Unlocks the semaphore of the main final process
            }
            sem_post(s_num_block);
            sem_post(s_line_block);

            exit(0);
        }
        else if (deer < 0)
        {
            fprintf(stderr,"ERROR:Failed to create process deer\n");
            fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
            fprintf(stderr,"All records in the file proj2.out are not valid\n");
            quantity->error = true;
            for(int f = 0; f < 3; f++) // If the process has not been created, we allow the main process to close all the closures to terminate the program abnormally
            {
                sem_post(s_end_block);
            }
            exit(ERROR);
        }
    }
}


int main(int argc, char **argv)
{
    t_arguments arguments = cheking_entered(argc, argv); // Filling in the arguments
    start_all(); //We combine memory, create semaphores, open a file for writing, defines starting values for counters

    pid_t santa = fork(); // Split main process
    if(santa == 0)
    {
        santa_life(&arguments); // Calling the santa function
    }
    else if(santa > 0)
    {
        pid_t child_process_2 =fork(); //Split main process
        if(child_process_2 == 0)
        {
            pid_t child_process_2_1 =fork(); //Split child_process_2 process
            if(child_process_2_1 == 0)
            {
                elves_life(&arguments);// Calling the elves function
            }
            else if(child_process_2_1 > 0)  //Split main process
            {
                deer_life(&arguments);  // Calling the deer function
            }
            else if(child_process_2_1 == ERROR)
            {
                fprintf(stderr,"ERROR:Failed to create another process\n");
                fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
                fprintf(stderr,"All records in the file proj2.out are not valid\n");
                quantity->deer_waiting = arguments.NR;
                sem_post(s_bed_block);  //In case of unsuccessful separation of processes, open all Santa's semaphores to exit
                sem_post(s_christmas_block);
                for(int f = 0; f < 3; f++) //Waiting for all processes to finish
                {
                    sem_post(s_end_block);
                }
                exit(ERROR);
            }
        }
        else if (child_process_2 > 0)
        {
            for(int f = 0; f < 3; f++) //Waiting for all processes to finish
            {
                sem_wait(s_end_block);
            }

            if(quantity->error == true)
            {
                fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
                fprintf(stderr,"All records in the file proj2.out are not valid\n");
                closing_all(); // all closing
                exit(ERROR);
            }
            closing_all(); // all closing
        }
        else if (child_process_2 == ERROR)
        {
            fprintf(stderr,"ERROR:Failed to create another process\n");
            fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
            fprintf(stderr,"All records in the file proj2.out are not valid\n");
            quantity->deer_waiting = arguments.NR;
            sem_post(s_bed_block);  //In case of unsuccessful separation of processes, open all Santa's semaphores to exit
            sem_post(s_christmas_block);
            closing_all();// all closing
            exit(ERROR);
        }

    }
    else if(santa == ERROR)
    {
        fprintf(stderr,"ERROR:Failed to create santa process\n");
        fprintf(stderr,"ABNORMAL PROGRAM TERMINATION\n");
        fprintf(stderr,"All records in the file proj2.out are not valid\n");
        closing_all();// all closing
        exit(ERROR);
    }

    return 0;
}
