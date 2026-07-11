#include <dos.h>
#include <i86.h>

#include "Biostime.h"


static uint8_t bcdToBin( uint8_t x ) {
  return ( (x >> 4) * 10 ) + ( x & 0x0f );
}


uint32_t getRtcSecondsSinceMidnight( void ) {

  union REGS regs;

  regs.h.ah = 0x02;      // BIOS RTC: get time
  int86( 0x1a, &regs, &regs );

  if ( regs.x.cflag ) {
    return 0xfffffffful;
  }

  uint8_t hour = bcdToBin( regs.h.ch );
  uint8_t min  = bcdToBin( regs.h.cl );
  uint8_t sec  = bcdToBin( regs.h.dh );

  return (uint32_t)hour * 3600ul +
         (uint32_t)min  * 60ul +
         (uint32_t)sec;
}

uint32_t rtcElapsedSeconds( uint32_t start, uint32_t end ) {

  if ( end >= start ) {
    return end - start;
  }

  // Midnight rollover
  return ( 24ul * 3600ul - start ) + end;
}
