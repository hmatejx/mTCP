#ifndef BIOSTIME_H
#define BIOSTIME_H

#include "types.h"

extern uint32_t getRtcSecondsSinceMidnight( void );
extern uint32_t rtcElapsedSeconds( uint32_t start, uint32_t end );

#endif