/**************************************************************************
 File name:		  airport.h
 Author:        Liam Henry
 Date:          11.1.21
 Class:         CS300
 Assignment:    Airport
 Purpose:       This file defines the constants, data structures, and
                function prototypes for the Airport assignment
 *************************************************************************/

#ifndef INCLUDE_AIRPORT_H_
#define INCLUDE_AIRPORT_H_

#include <stdbool.h>
#include "../../PriorityQueueADT/include/pqueue.h"
#include "../../QueueADT/include/queue.h"
#include "../../ListADT/include/list.h"

typedef struct Airport *AirportPtr;
typedef struct Airport
{
		Queue sRunway;
		PriorityQueue sLanding;
		int time;
		int takeoff, land, fuel1, fuel2, fuel3;
		char runway1, runway2, runway3;
}Airport;

typedef struct Stats *StatsPtr;
typedef struct Stats
{
		int zeroFuel, crash;
		double averageLandingWait, averageTakeoffWait, averageFlyingTime;
		double totalTakeoff, totalLanding;
}Stats;

extern void setTime (AirportPtr psAirport);

extern void setStats(StatsPtr psStats);

extern void airportRead (AirportPtr psAirport, int takeoff, int land,
		int fuel[]);

extern void clearAirport(AirportPtr psAirport);

extern void enqueueAirport(AirportPtr psAirport, StatsPtr psStats, int takeoff,
		int land, int fuel[], int change);

extern void planeCrash(StatsPtr psStats, AirportPtr psAirport, int waitingTime);

extern void emergencyDequeue(AirportPtr psAirport, StatsPtr psStats,
		int* fuelBuffer);

extern void landingDequeue(AirportPtr psAirport, StatsPtr psStats,
		int* fuelBuffer);

extern void takeoffDequeue(AirportPtr psAirport, StatsPtr psStats);

extern void crashDequeue(AirportPtr psAirport, StatsPtr psStats);

extern bool landingIsEmpty(AirportPtr psAirport);

extern bool takeoffIsEmpty(AirportPtr psAirport);

extern void airportChangeFuel(AirportPtr psAirport, int fuelChange);

extern void runwayEmergency(AirportPtr psAirport, int runway);

extern void runwayLand(AirportPtr psAirport, int runway);

extern void runwayTakeoff(AirportPtr psAirport, int runway);

extern int takeoffSize(AirportPtr psAirport);

extern int landSize(AirportPtr psAirport);

extern void *landPeek(AirportPtr psAirport, void* waitingTime, int size, int* fuel);

#endif /* AIRPORT_H */
