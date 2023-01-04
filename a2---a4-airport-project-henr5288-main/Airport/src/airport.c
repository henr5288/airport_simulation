/**************************************************************************
 File name:  airport.c
 Author:     Liam Henry
 Date:		 	 11.1.16
 Class:		   CS300
 Assignment: Aiport
 Purpose:    Implementation for Airport assignment
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../QueueADT/include/queue.h"
#include "../../PriorityQueueADT/include/pqueue.h"
#include "../include/airport.h"

/**************************************************************************
 Function: 	 	setTime

 Description:	sets airport time to one

 Parameters:	psAirport - a pointer to Airport

 Returned:	 	None
 *************************************************************************/
void setTime (AirportPtr psAirport)
{
	psAirport->time = 1;
}

/**************************************************************************
 Function: 	 	setStats

 Description:	sets stats in stat struct to zero

 Parameters:	psStats - pointer to Stats

 Returned:	 	None
 *************************************************************************/
void setStats(StatsPtr psStats)
{
	psStats->averageLandingWait = psStats->averageTakeoffWait =
			psStats->averageFlyingTime = 0;
	psStats->crash = psStats->totalLanding = psStats->totalTakeoff = 0;
	psStats->zeroFuel = 0;
}

/**************************************************************************
 Function: 	 	airportRead

 Description:	sets variables in airprot

 Parameters:	psAirport - a pointer to Airport
 	 	 	 	 	 	  takeoff   - number of planes taking off
 	 	 	 	 	 	  land      - number of planes landing
 	 	 	 	 	 	  fuel[]    - fuel for each plane entered

 Returned:	 	None
 *************************************************************************/
void airportRead (AirportPtr psAirport, int takeoff, int land, int fuel[])
{
	psAirport->takeoff = takeoff;
	psAirport->land = land;
	psAirport->fuel1 = fuel[0];
	psAirport->fuel2 = fuel[1];
	psAirport->fuel3 = fuel[2];
}

/**************************************************************************
 Function: 	 	clearAirport

 Description:	sets runways and fuel back to default

 Parameters:	psAirport - a pointer to Airport

 Returned:	 	None
 *************************************************************************/
void clearAirport(AirportPtr psAirport)
{
	psAirport->runway1 = psAirport->runway2 = psAirport->runway3 = '-';
	psAirport->fuel1 = psAirport->fuel2 = psAirport->fuel3 = 0;
}

/**************************************************************************
 Function: 	 	enqueueAirport

 Description:	enqueues planes into the priority and regular queue

 Parameters:	psAirport - a pointer to Airport

 Returned:	 	None
 *************************************************************************/
void enqueueAirport(AirportPtr psAirport, StatsPtr psStats, int takeoff,
		int land, int fuel[], int change)
{
	for (int i = 0; i < land; i++)
	{
		pqueueEnqueue(&psAirport->sLanding, &psAirport->time, sizeof(int), fuel[i]);
		psStats->totalLanding++;
	}

	for (int i = 0; i < takeoff; i++)
	{
		queueEnqueue(&psAirport->sRunway, &psAirport->time, sizeof(int));
		psStats->totalTakeoff++;
	}
}

/**************************************************************************
 Function: 	 	planeCrash

 Description:	sets variables depending on if plane crashed

 Parameters:	psStats     - pointer to Stats
 	 	 	 	 	 	 	psAirport   - pointer to Airport
 	 	 	 	 	 	 	waitintTime - plane waiting time

 Returned:	 	None
 *************************************************************************/
void planeCrash(StatsPtr psStats, AirportPtr psAirport, int waitingTime)
{
	psStats->crash++;
	psStats->averageLandingWait = psStats->averageLandingWait +
			(psAirport->time - waitingTime);
}

/**************************************************************************
 Function: 	 	emergencyDequeue

 Description:	dequeues plane from landing queue due to emergency

 Parameters:  psAirport  - pointer to Airport
 	 	 	 	 	 	  psStats    - pointer to Stats
 	 	 	 	 	 	  fuelBuffer - pointer to fuel of plane

 Returned:	 	None
 *************************************************************************/
void emergencyDequeue(AirportPtr psAirport, StatsPtr psStats, int* fuelBuffer)
{
	int waitingBuffer;
	pqueueDequeue(&psAirport->sLanding, &waitingBuffer, sizeof(int), fuelBuffer);
	psStats->zeroFuel++;
	psStats->averageLandingWait = psStats->averageLandingWait +
			(psAirport->time - waitingBuffer);
}

/**************************************************************************
 Function: 	 	landingDequeue

 Description:	dequeues plane from landing queue

 Parameters:  psAirport  - pointer to Airport
  	 	 	 	 	  psStats    - pointer to Stats
 	 	 	 	 	 	  fuelBuffer - pointer to fuel of plane

 Returned:	 	None
 *************************************************************************/
void landingDequeue(AirportPtr psAirport, StatsPtr psStats, int* fuelBuffer)
{
	int waitingBuffer;
	pqueueDequeue(&psAirport->sLanding, &waitingBuffer, sizeof(int), fuelBuffer);
	psStats->averageLandingWait = psStats->averageLandingWait +
			(psAirport->time - waitingBuffer);
	psStats->averageFlyingTime = psStats->averageFlyingTime + *fuelBuffer;
}

/**************************************************************************
 Function: 	 	takeoffDequeue

 Description:	dequeues plane from takeoff queue

 Parameters:  psAirport - pointer to Airport
  	 	 	 	 	  psStats   - pointer to Stats

 Returned:	 	None
 *************************************************************************/
void takeoffDequeue(AirportPtr psAirport, StatsPtr psStats)
{
	int waitingBuffer;
	queueDequeue(&psAirport->sRunway, &waitingBuffer, sizeof(int));
	psStats->averageTakeoffWait = psStats->averageTakeoffWait +
			(psAirport->time - waitingBuffer);
}

/**************************************************************************
 Function: 	 	crashDequeue

 Description:	dequeues a crashed plane

 Parameters:  psAirport  - pointer to Airport
  	 	 	 	 	  psStats    - pointer to Stats
  	 	 	 	 	  totalCrash - number of planes that have crashed per turn

 Returned:	 	None
 *************************************************************************/
void crashDequeue(AirportPtr psAirport, StatsPtr psStats)
{
	int waitingBuffer;
	int fuelBuffer;
	pqueueDequeue(&psAirport->sLanding, &waitingBuffer, sizeof(int), &fuelBuffer);
	planeCrash(psStats, psAirport, waitingBuffer);
}

/**************************************************************************
 Function: 	 	landingIsEmpty

 Description:	testing if landing queue is empty

 Parameters:  psAirport  - pointer to Airport

 Returned:	 	bool based on result of pqueueIsEmpty
 *************************************************************************/
bool landingIsEmpty(AirportPtr psAirport)
{
	return pqueueIsEmpty(&psAirport->sLanding);
}

/**************************************************************************
 Function: 	 	takeoffIsEmpty

 Description:	testing if takeoff queue is empty

 Parameters:  psAirport  - pointer to Airport

 Returned:	 	bool based on result of queueIsEmpty
 *************************************************************************/
bool takeoffIsEmpty(AirportPtr psAirport)
{
	return queueIsEmpty(&psAirport->sRunway);
}

/**************************************************************************
 Function: 	 	airportChangeFuel

 Description:	changing priority of queue elements

 Parameters:  psAirport  - pointer to Airport
 	 	 	 	 	 	  fuelChange - value to change fule by

 Returned:	  none
 *************************************************************************/
void airportChangeFuel(AirportPtr psAirport, int fuelChange)
{
	pqueueChangePriority(&psAirport->sLanding, fuelChange);
}

/**************************************************************************
 Function: 	 	runwayEmergency

 Description:	setting runways to emergency

 Parameters:  psAirport - pointer to Airport
 	 	 	 	 	 	  runway    - number of runways

 Returned:	 	none
 *************************************************************************/
void runwayEmergency(AirportPtr psAirport, int runway)
{
	const char EMERGENCY = 'E';
	if (runway == 3)
	{
		psAirport->runway1 = EMERGENCY;
	}
	else if (runway == 2)
	{
		psAirport->runway2 = EMERGENCY;
	}
	else if (runway == 1)
	{
		psAirport->runway3 = EMERGENCY;
	}
}

/**************************************************************************
 Function: 	 	runwayLand

 Description:	setting runways to land

 Parameters:  psAirport - pointer to Airport
 	 	 	 	 	 	  runway    - number of runways

 Returned:	 	none
 *************************************************************************/
void runwayLand(AirportPtr psAirport, int runway)
{
	const char LAND = 'L';
	if (runway == 3)
	{
		psAirport->runway1 = LAND;
	}
	else if (runway == 2)
	{
		psAirport->runway2 = LAND;
	}
	else if (runway == 1)
	{
		psAirport->runway3 = LAND;
	}
}

/**************************************************************************
 Function: 	 	runwayTakeoff

 Description:	setting runways to takeoff

 Parameters:  psAirport - pointer to Airport
 	 	 	 	 	 	  runway    - number of runways

 Returned:	 	none
 *************************************************************************/
void runwayTakeoff(AirportPtr psAirport, int runway)
{
	const char TAKEOFF = 'T';
	if (runway == 3)
	{
		psAirport->runway1 = TAKEOFF;
	}
	else if (runway == 2)
	{
		psAirport->runway2 = TAKEOFF;
	}
	else if (runway == 1)
	{
		psAirport->runway3 = TAKEOFF;
	}
}

/**************************************************************************
 Function: 	 	takeoffSize

 Description:	takeoff queue size

 Parameters:  psAirport - pointer to Airport

 Returned:	 	size of queue
 *************************************************************************/
int takeoffSize(AirportPtr psAirport)
{
	return queueSize(&psAirport->sRunway);
}

/**************************************************************************
 Function: 	 	landSize

 Description:	landing queue size

 Parameters:  psAirport - pointer to Airport

 Returned:	 	size of queue
 *************************************************************************/
int landSize(AirportPtr psAirport)
{
	return pqueueSize(&psAirport->sLanding);
}

/**************************************************************************
 Function: 	 	landPeek

 Description:	peeks at the first of the pqueue

 Parameters:	psAirport    - pointer to a airport
 	 	 	 	 	 	  *waitingTime - pointer to data
 	 	 	 	 	 	  size 		     - size of data being passed in
 	 	 	 	 	 	  *fuel        - pointer to fuel of element

 Returned:	 	value of element
 *************************************************************************/
void *landPeek(AirportPtr psAirport, void* waitingTime, int size, int* fuel)
{
	pqueuePeek(&psAirport->sLanding, waitingTime, size, fuel);
	return waitingTime;
}





