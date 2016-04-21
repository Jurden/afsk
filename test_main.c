#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "encoder.h"
#include "crc.h"
#include "ax25.h"
#include "afsk.h"

int main(int argc, char *argv[])
{
	if(argc == 1) {
		printf("Jordan's Test Code\n");
		printf("Usage: 'cmd' 'arg'\n");
		printf("cmd         arg\n");
		printf("1 - Test AX25");
		printf("2 - Test locking, ");
		return 0;
	} 
	switch (argv[2]) {
		case 1:
			if(argc == 3) {

			printf("
