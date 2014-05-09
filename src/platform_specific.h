#pragma once

#ifdef __GNUC__
	#include <stdbool.h>
#else
	#define true 1
	#define false 0
	#define bool int
	#ifndef NULL
		#define NULL 0
	#endif	
	#define inline __inline
#endif