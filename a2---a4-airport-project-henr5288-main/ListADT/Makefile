###########################################################################
# File name:  Makefile
# Author:     Liam Henry
# Date:       9.19.21
# Class:      CS 300
# Assignment: Dynamic List
# Purpose: 	  This is the Makefile for the Dynamic List    
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/listdriver

bin:
	mkdir -p bin

bin/listdriver: bin/listdriver.o bin/list.o
	${CC} ${CFLAGS} bin/listdriver.o bin/list.o -o bin/listdriver

bin/listdriver.o: src/listdriver.c include/list.h
	${CC} ${CFLAGS} -c src/listdriver.c -o bin/listdriver.o
	
bin/list.o: src/list.c include/list.h
	${CC} ${CFLAGS} -c src/list.c -o bin/list.o

clean:
	rm -rf bin/*.o bin/listdriver