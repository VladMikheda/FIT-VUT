

PROJECT=IPK2022

CC = g++
CFLAGS= -Wall -Wextra -pedantic
FILES=$(wildcard *.cpp)

all: IPK2022


IPK2022:
	$(CC) $(CFLAGS) $(FILES) -o hinfosvc

test:
	./hinfosvc 12345

clean:
	rm -f hinfosvc
