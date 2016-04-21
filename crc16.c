// Adapted from http://stjarnhimlen.se/snippets/crc-16.c 
#include "stdio.h"
#define POLY 0x8408
unsigned short crc16(char *data_p, unsigned short length)
{
	unsigned char i;
	unsigned int data;
	unsigned int crc = 0xFFFF;

	if (length == 0)
	return (~crc);

	do
	{
		for (i=0, data=(unsigned int)0xff & *data_p++;
			i < 8; 
			i++, data >>= 1)
			{
			if ((crc & 0x0001) ^ (data & 0x0001))
			crc = (crc >> 1) ^ POLY;
			else  crc >>= 1;
		}
	} while (--length);

	return (~crc);
}
