#ifndef __TON_H_
#define __TON_H_

typedef struct
{
	unsigned long start_tick;
	unsigned long duration;
} TOn;

/// <summary>
/// Initializes a TOn data structure representing a Timer.
/// </summary>
/// <param name="ton">The timer data structure to initialize</param>
void TOn_Initialize(TOn* ton);

/// <summary>
/// Starts a timer with the corresponding duration.
/// </summary>
/// <param name="ton">The timer to start</param>
/// <param name="duration">Timer duration in ms</param>
void TOn_Start(TOn* ton, int duration);

/// <summary>
/// Determines if a timer has elapsed.
/// </summary>
/// <param name="ton">The timer</param>
/// <returns>1 if the timer is elapsed, 0 otherwise.</returns>
char TOn_IsElapsed(TOn* ton);

#endif