// Borrowed from Seth Raymond for AFSK
#ifndef AX25
#define AX25

#include <sys/types.h>
#include <stdint.h>

uint8_t* ax25(char *callsign, char *info, int size);

#endif
