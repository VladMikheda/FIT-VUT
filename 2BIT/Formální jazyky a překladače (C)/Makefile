#
#  Project: Implementace překladače imperativního jazyka IFJ21
#
#  Subject:  IFJ2021
#
#  @author:  Vladislav Mikheda      xmikhe00
#  @author:  Khrisanov Vladislav    xkhris00
#  @author:  Kilybayev Anvar        xkilyb00
#  @author:  Gazizov Zhasdauren     xgaziz00
#

PROJECT=ifj2021

CC = gcc
CFLAGS=-std=gnu99 -Wall -Wextra -Werror -pedantic -pthread
FILES=$(wildcard *.c)

all: ifj2021


ifj2021:
	$(CC) $(CFLAGS) $(FILES) -o main 

test:
	./main test.txt

clean:
	rm -f main

# all:
# 	gcc -std=gnu99 -Wall -Wextra -Werror -pedantic -pthread *.c -o proj
