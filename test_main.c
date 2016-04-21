#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "encoder.h"
#include "crc16.h"
#include "ax25.h"
//#include "afsk.h"
int test_ax25(char *data);
int main(int argc, char *argv[])
{
	if(argc == 1) {
		printf("Jordan's Test Code\n");
		printf("Usage: 'cmd' 'arg'(if any)\n");
		printf("	cmd		arg\n");
		printf("1 - Test AX25, 		data\n");
		printf("2 - Test locking, 	no arg\n");
		printf("3 - ioctl Query, 	no arg\n");
		printf("4 - ioctl Set, 		# of delims\n");
		return 0;
	}/* 
	switch (argv[2]) {
		case 1:
			if(argc == 3) {

			printf("
			*/
}
