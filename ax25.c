// Borrowed from Seth Raymond for testing AFSK
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ax25.h"
#include "crc.h"

#define DA_IDX 0
#define DA_SSID_IDX 6
#define SA_IDX 7
#define SA_SSID_IDX 13
#define L2RA_IDX 14
#define L2RA_SSID_IDX 20
#define CTRL_0_IDX 21
#define CTRL_1_IDX 22
#define INFO_IDX 23

uint8_t* ax25(char *callsign, char *info, int size)
{
	int i;
	char dest[] = "APZUME";
	uint8_t da_ssid = 0;
	uint8_t sa_ssid = 11;
	char l2ra[] = "WIDE2 ";
	uint8_t l2ra_ssid = 1;
	uint8_t *buffer;
	uint16_t crc;
	
	if (size > 256) return NULL;
	buffer = (uint8_t*)malloc(25+size);

	//store dest into buffer
	for (i=0;i<6;i++) {
		buffer[DA_IDX+i] = dest[i] << 1;
	}

	//store dest ssid into buffer
	
	buffer[DA_SSID_IDX] = 0x60 | (da_ssid << 1) | 0x00;
	
	//store src (callsign) into buffer	

	if (strlen(callsign) != 6) return NULL;
	for (i=0;i<6;i++) { //standard says 6 char callsign
		buffer[SA_IDX+i] = callsign[i] << 1;
	}

	//store src (callsign) ssid into buffer

	buffer[SA_SSID_IDX] = 0x60 | (sa_ssid << 1) | 0x00;

	//store L2RA into buffer

	for (i=0;i<6;i++) {
		buffer[L2RA_IDX+i] = l2ra[i] << 1;
	}

	//store L2RA ssid into buffer

	buffer[L2RA_SSID_IDX] = 0x60 | (l2ra_ssid << 1) | 0x01;

	//set up ctrl values

	buffer[CTRL_0_IDX] = 0x03;
	buffer[CTRL_1_IDX] = 0xF0;

	//store info, passed into function
	memcpy(buffer+INFO_IDX,info,size);
	
	//calculate crc on everything until the last byte of info,
	//which avoids the null terminator

	crc = calcCRC(buffer,INFO_IDX+size);
	memcpy(buffer+23+size,&crc,2);

	write(1,buffer,25+size);

	return buffer;
	//free(buffer);	

}
