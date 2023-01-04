###########################################################################
# File name:  Makefile
# Author:     Liam Henry
# Date:       10.30.21
# Class:      CS 300
# Assignment: Airport
# Purpose: 	  This is the Makefile for the Airport
###########################################################################

CC=gcc
CFLAGS=-Wall -g

.PHONY: all clean

all: bin bin/airportdriver

bin:
	mkdir -p bin

bin/airportdriver: bin/airportdriver.o bin/airport.o ../PriorityQueueADT/bin/pqueue.o ../QueueADT/bin/queue.o ../ListADT/bin/list.o
	${CC} ${CFLAGS} bin/airportdriver.o bin/airport.o ../PriorityQueueADT/bin/pqueue.o ../QueueADT/bin/queue.o ../ListADT/bin/list.o -o bin/airportdriver 
	
bin/airport.o: src/airport.c include/airport.h ../PriorityQueueADT/include/pqueue.h ../QueueADT/include/queue.h ../ListADT/include/list.h
	${CC} ${CFLAGS} -c src/airport.c -o bin/airport.o ../PriorityQueueADT/bin/pqueue.o ../ListADT/bin/list.o ../QueueADT/bin/queue.o
	
bin/airportdriver.o: src/airportdriver.c include/airport.h
	${CC} ${CFLAGS} -c src/airportdriver.c -o bin/airportdriver.o
	
../PriorityQueueADT/bin/pqueue.o:
	cd ../PriorityQueueADT; make bin/pqueue.o
	
../ListADT/bin/list.o:
	cd ../ListADT; make bin/list.o
	
../QueueADT/bin/queue.o:
	cd ../QueueADT; make bin/queue.o
	
clean:
	rm -rf bin/*.o bin/airportdriver
	
vlagrind: bin/airportdriver
	valgrind -v --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all bin/aiportdriver

	