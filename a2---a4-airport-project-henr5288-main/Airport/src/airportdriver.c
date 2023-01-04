/*******************************************************************************
 File name:  queuedriver.c
 Author:     Liam Henry
 Date:		   11.1.21
 Class:		   CS300
 Assignment: Airport
 Purpose:    Driver for testing the airport assinment
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/airport.h"
#include "../../ListADT/include/list.h"
#include "../../PriorityQueueADT/include/pqueue.h"
#include "../../QueueADT/include/queue.h"

/****************************************************************************
 Function: 	 	printHeader

 Description: prints the header for the airport output

 Parameters:	none

 Returned:	 	none
 ****************************************************************************/
static void printHeader()
{
	printf("     |           Planes Added            |      Runways      |   "
			"Queue  Lengths\n");
	printf("Time | Takeoff  Landing (Fuel Remaining) |  1   2   3  Crash | "
			"Takeoff  Landing\n");
	printf("---- | -------  ------------------------ | --- --- --- ----- | "
			"-------  -------\n");
}

/****************************************************************************
 Function: 	 	printData

 Description: prints the data for each turn

 Parameters:	takeoff  - number of planes taking off
 	 	 	 	 	 	 	landing  - number of planes landing
 	 	 	 	 	 	 	fuel[]   - fuel of each plane entered
 	 	 	 	 	 	 	sAirport - airport struct
 	 	 	 	 	 	 	psStats  - stats of airport

 Returned:	 	none
 ****************************************************************************/
static void printData(int takeoff, int landing, int fuel[],
		Airport sAirport, StatsPtr psStats, int crash)
{
	printf("%4d |       %d        %d |", sAirport.time, takeoff,
			landing);

	if (sAirport.fuel1 == 0 || sAirport.fuel2 == 0 || sAirport.fuel3 == 0)
	{
		if (sAirport.fuel1 == 0)
		{
			printf("    -");
		}
		else{
			printf("    %d", sAirport.fuel1);
		}
		if (sAirport.fuel2 == 0)
		{
			printf("    -");
		}
		else
		{
			printf("    %d", sAirport.fuel2);
		}
		if (sAirport.fuel3 == 0)
		{
			printf("    - |");
		}
		else
		{
			printf("    %d |", sAirport.fuel3);
		}
	}
	else
	{
		printf(" %4d %4d %4d |", sAirport.fuel1, sAirport.fuel2,
				sAirport.fuel3);
	}

	printf("  %c   %c   %c      %d |", sAirport.runway1, sAirport.runway2,
			sAirport.runway3, crash);

	printf("    %4d     %4d\n", queueSize(&sAirport.sRunway),
			pqueueSize(&sAirport.sLanding));

}

/****************************************************************************
 Function: 	 	printStats

 Description: prints the stats of airport at end of program

 Parameters:	psAirport - airport struct
 	 	 	 	 	 	 	psStats  - stats of airport

 Returned:	 	none
 ****************************************************************************/
static void printStats (AirportPtr psAirport, StatsPtr psStats)
{
	float takeoffTime = (psStats->averageTakeoffWait + psStats->totalTakeoff)
			/ psStats->totalTakeoff;
	float landingTime = (psStats->averageLandingWait + psStats->totalLanding)
			/ psStats->totalLanding;
	float flyingTime = psStats->averageFlyingTime / psStats->totalLanding;

	printf("\nAverage takeoff waiting time: %g\n",
			takeoffTime);
	printf("Average landing waiting time: %g\n", landingTime);
	printf("Average flying time remaining on landing: %g\n", flyingTime);
	printf("Number of planes landing with zero fuel: %d\n", psStats->zeroFuel);
	printf("Number of crashes: %d", psStats->crash);
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the airport

 Parameters:	none
 Returned:	 	none
 *************************************************************************/
int main (int argc, char *argv[])
{
	const int FUEL_CHANGE = -1;
	const int MAX_RUNWAYS = 3;
	const int TWO_RUNWAYS = 2;
	const int ONE_RUNWAY = 1;
	const int NEW_HEADER = 20;
	const int RESET = 100;

	int buffer, fuelBuffer;
	int takeoff, land;
	int fuel[2];
	int runways = 3;
	int totalCrash = 0;

	FILE* data = NULL;

	Airport sAirport;
	Stats sStats;

	printHeader();

	pqueueLoadErrorMessages();
	lstLoadErrorMessages();
	queueLoadErrorMessages();

	data = fopen(argv[1], "r");
	if (data == NULL)
	{
		printf("Could not open file data.txt\n");
		return -1;
	}

	pqueueCreate(&sAirport.sLanding);
	queueCreate(&(sAirport.sRunway));

	setTime(&sAirport);
	clearAirport(&sAirport);
	setStats(&sStats);

	while (!feof(data) || !(landingIsEmpty(&sAirport)) ||
			!(takeoffIsEmpty(&sAirport)))
	{
		if (!feof(data))
		{
			fscanf(data, "%d", &buffer);
			takeoff = buffer;
			fscanf(data, "%d", &buffer);
			land = buffer;
			fscanf(data, "%d", &fuel[0]);
			fscanf(data, "%d", &fuel[1]);
			fscanf(data, "%d", &fuel[2]);

			airportRead(&sAirport, takeoff, land, fuel);
			enqueueAirport(&sAirport, &sStats, takeoff, land, fuel, FUEL_CHANGE);
		}

		if (!(landingIsEmpty(&sAirport)))
		{
			airportChangeFuel(&sAirport, FUEL_CHANGE);
			landPeek(&sAirport, &buffer, sizeof(int), &fuelBuffer);
		}

		// Dequeueing emergency planes
		while (fuelBuffer == 0 && runways > 0)
		{
			if (!(landingIsEmpty(&sAirport)))
			{
				emergencyDequeue(&sAirport, &sStats, &fuelBuffer);

				if (runways == MAX_RUNWAYS)
				{
					runwayEmergency(&sAirport, runways);
					runways--;
				}
				else if (runways == TWO_RUNWAYS)
				{
					runwayEmergency(&sAirport, runways);
					runways--;
				}
				else if (runways == ONE_RUNWAY)
				{
					runwayEmergency(&sAirport, runways);
					runways--;
				}
				if (!(landingIsEmpty(&sAirport)))
				{
					landPeek(&sAirport, &buffer, sizeof(int), &fuelBuffer);
				}
			}
			else {
				fuelBuffer = RESET;
			}
		}

		// Testing for crashed planes
		if (!(landingIsEmpty(&sAirport)))
		{
			landPeek(&sAirport, &buffer, sizeof(int), &fuelBuffer);

			while (fuelBuffer == 0)
			{
				if (!(landingIsEmpty(&sAirport)))
				{
					crashDequeue(&sAirport, &sStats);
					totalCrash++;
				}
				else {
					fuelBuffer = RESET;
				}
			}
		}

		// Dequeueing landing and takeoff planes
		while (runways > 0)
		{
			if (landSize(&sAirport) >= takeoffSize(&sAirport))
			{
				if (!(landingIsEmpty(&sAirport)))
				{
					landingDequeue(&sAirport, &sStats, &fuelBuffer);

					if (runways == MAX_RUNWAYS)
					{
						runwayLand(&sAirport, runways);
						runways--;
					}
					else if (runways == TWO_RUNWAYS)
					{
						runwayLand(&sAirport, runways);
						runways--;
					}
					else if (runways == ONE_RUNWAY)
					{
						runwayLand(&sAirport, runways);
						runways--;
					}
				}
				if (landingIsEmpty(&sAirport))
				{
					runways = 0;
				}
			}
			else
			{
				if (!(takeoffIsEmpty(&sAirport)))
				{
					takeoffDequeue(&sAirport, &sStats);

					if (runways == MAX_RUNWAYS)
					{
						runwayTakeoff(&sAirport, runways);
						runways--;
					}
					else if (runways == TWO_RUNWAYS)
					{
						runwayTakeoff(&sAirport, runways);
						runways--;
					}
					else if (runways == ONE_RUNWAY)
					{
						runwayTakeoff(&sAirport, runways);
						runways--;
					}
				}
				if (takeoffIsEmpty(&sAirport))
				{
					runways = 0;
				}
			}
		}

		printData(takeoff, land, fuel, sAirport, &sStats, totalCrash);

		if (sAirport.time == NEW_HEADER)
		{
			printf("\n");
			printHeader();
		}

		clearAirport(&sAirport);
		sAirport.time++;
		runways = MAX_RUNWAYS;
		takeoff = land = 0;
		fuelBuffer = 0;
		totalCrash = 0;
	}

	printStats(&sAirport, &sStats);

	pqueueTerminate(&sAirport.sLanding);
	queueTerminate(&sAirport.sRunway);

	fclose(data);

	return 0;
}
