#include "delta_time.h"

#include <time.h>

static double dt;

#ifdef __GNUC__
	#include <sys/time.h>

	#include "useful.h"

	static struct timeval last_tick;

	void dt_start()
	{
		gettimeofday(&last_tick, NULL);  
	}

	double dt_get()
	{
		struct timeval this_tick;
    gettimeofday(&this_tick, NULL);    
    dt = MAX(0.0, MICROSECONDS_TO_SECONDS(this_tick.tv_usec - last_tick.tv_usec));
    last_tick = this_tick;

		return dt;
	}

#else
	#include <windows.h>

	static LARGE_INTEGER frequency, last_tick;

	void dt_start()
	{
    QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&last_tick);
	}

	double dt_get()
	{
		LARGE_INTEGER this_tick;
		QueryPerformanceCounter(&this_tick);
		dt = (this_tick.QuadPart - last_tick.QuadPart) * 1000.0 / frequency.QuadPart;
		last_tick = this_tick;

		return dt;
	}

#endif