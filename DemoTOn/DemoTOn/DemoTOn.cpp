// DemoTOn.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "Ton.h"
#include "modbus.h"

#define PERIOD 250

int main()
{
	TOn timer;
	TOn_Initialize(&timer);
	for (;;)
	{
		if (TOn_IsElapsed(&timer))
		{
			printf("Tick\n");
			TOn_Start(&timer, PERIOD);
		}
	}
	printf("Hello\n");
}

