#
# Project: Model vytapeni (Teplarenstvi)
#
# Subject:  IMS 2022
#
# @author:  Vladislav Mikheda  xmikhe00
# @author:  Vladislav Khrisanov xkhris00
#

PROJECT=IMS2022

CC = g++
CFLAGS= -Wall -Wextra -pedantic
FILES=$(wildcard *.cpp)

all: IMS2022


IMS2022:
	$(CC) $(CFLAGS) $(FILES) -o ims

run:
	./ims '0'

run5:
	./ims '-5'

clean:
	rm -f ims