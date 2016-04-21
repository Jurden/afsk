#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "encoder.h"
#include "crc16.h"
#include "ax25.h"
#include "afsk.h"
int test_afsk(char *callsign, char *data);
int test_lock();
int test_query();
int test_set(int delim_n);
int main(int argc, char *argv[])
{
	int test;
	int ret;
	if(argc == 1) {
		printf("Jordan's Test Code\n");
		printf("Usage: 'cmd' 'arg'\n");
		printf("cmd			arg(s)\n");
		printf(" 1 - Test afsk, 	callsign, data\n");
		printf(" 2 - Test locking, 	no arg\n");
		printf(" 3 - ioctl Query, 	no arg\n");
		printf(" 4 - ioctl Set, 	# of delims\n");
		return 0;
	}
	test = atoi(argv[1]);
	switch (test) {
		case 1:
			if(argc != 4) {
				printf("Include data for afsk\n");
				return -1;
			}
			ret = test_afsk(argv[2], argv[3]);
			return 0;
		case 2:
			if(argc != 2) {
				printf("Test doesn't require arg\n");
				return -1;
			}
			return 0;
		case 3:
			if(argc != 2) {
				printf("Test doesn't require arg\n");
				return -1;
			}
			return 0;
		case 4:
			if(argc != 3) {
				printf("Include number of delims\n");
				return -1;
			}
			return 0;
	}
}
int test_afsk(char *callsign, char *data) {
	int fd;
	int size;
	int ret;
	printf("FD\n");
	fd = open("/dev/afsk",O_WRONLY);
	printf("%d\n",fd);

		
	return 0;
}
int test_lock() {
	return 0;
}
int test_query() {
	return 0;
}
int test_set(int delim_n) {
	return 0;	
}
