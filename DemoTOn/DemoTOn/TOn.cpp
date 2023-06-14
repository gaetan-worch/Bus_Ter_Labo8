#include "Ton.h"
#include <Windows.h>

void TOn_Initialize(TOn* ton)
{
	ton->duration = 0;
	ton->start_tick = 0;
}

void TOn_Start(TOn* ton, int duration)
{
	ton->start_tick = GetTickCount64();
	ton->duration = duration;
}

char TOn_IsElapsed(TOn* ton)
{
	return GetTickCount64() - ton->start_tick >= ton->duration;
}
