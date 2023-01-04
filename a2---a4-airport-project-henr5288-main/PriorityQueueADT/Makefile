###########################################################################
# File name:  Makefile
# Author:     Liam Henry
# Date:       10.11.21
# Class:      CS 300
# Assignment: Priority Queue
# Purpose: 	  This is the Makefile for the Priority Queue
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/pqueuedriver

bin:
	mkdir -p bin

bin/pqueuedriver: bin/pqueuedriver.o bin/pqueue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/pqueuedriver.o bin/pqueue.o ../ListADT/bin/list.o -o bin/pqueuedriver

bin/pqueue.o: src/pqueue.c include/pqueue.h ../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/pqueue.c -o bin/pqueue.o ../ListADT/bin/list.o 

bin/pqueuedriver.o: src/pqueuedriver.c include/pqueue.h
	${CC} ${CFLAGS} -c src/pqueuedriver.c -o bin/pqueuedriver.o

../ListADT/bin/list.o:
	cd ../ListADT; make bin/list.o
	
clean:
	rm -rf bin/*.o bin/pqueuedriver

vlagrind: bin/pqueuedriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all bin/pqueuedriver
	
