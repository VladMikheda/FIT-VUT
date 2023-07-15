#
# Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
#
# File:     Makefile
# Subject:  ISA 2022
#
#@author:  Vladislav Mikheda  xmikhe00
#

PROJECT=ISA2022

FILENAME = feedreader
CC=g++
CFLAGS = -W -Wall -Wextra -Werror -pedantic

FILESC=$(wildcard *.cpp)
XMLROOT =$(shell pkg-config --cflags libxml-2.0)
XMLLIB =$(shell pkg-config --libs libxml-2.0)

FILESC!=ls *.cpp
FILESH!=ls *.h
XMLROOT!=pkg-config --cflags libxml-2.0
XMLLIB!=pkg-config --libs libxml-2.0


LIB= -static-libstdc++ -lcrypto -lssl $(XMLLIB)


FILESP= Connect.cpp FeedReader.cpp ParseArguments.cpp UrlParser.cpp XMLParser.cpp
FILESTEST=tests/unit/*.cpp

all: ISA2022

ISA2022:
	$(CC) $(CFLAGS) $(FILESC) $(FILESH) -o $(FILENAME) $(XMLROOT) $(LIB)
RUN:
	./feedreader -f ./feedfile -a -u -T


TESTMYPC:
	$(CC)  $(CFLAGS) $(FILESTEST) $(FILESP) -o testfile  $(XMLROOT) $(LIB)
	./testfile
	$(CC) $(CFLAGS) $(FILESC) $(FILESH) -o $(FILENAME) $(XMLROOT) $(LIB)
	python ./tests/complex/test.py ''

test:
	$(CC)  $(CFLAGS) $(FILESTEST) $(FILESP) -o testfile  $(XMLROOT) $(LIB)
	./testfile nocert
	$(CC) $(CFLAGS) $(FILESC) $(FILESH) -o $(FILENAME) $(XMLROOT) $(LIB)
	python3 ./tests/complex/test.py '' nocert



