#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <malloc.h>
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
	int delim_cnt;
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
			delim_cnt = atoi(argv[2]);
			ret = test_set(delim_cnt);	
			return 0;
	}
}
int test_afsk(char *callsign, char *data) {
	int fd;
	int size;
	int ret;
	int i;
	uint8_t *buffer;
	
	printf("FD\n");
	fd = open("/dev/afsk",O_RDONLY);
	printf("%d \n",fd);	
	fd = open("/dev/afsk",O_WRONLY);
	if (fd < 0) {
		printf("Can't open device\n");
		return -1;
	}
	printf("%d\n",fd);
	size = strlen(data);
	buffer = (uint8_t *)malloc(size * 8 * sizeof(uint8_t));
	if (buffer == NULL) {
		printf("No memory");
		return -1;
	}
	for (i = 0; i < size*8*sizeof(uint8_t); i++) {
		if(i%2) {
			buffer[i] = 1;
		}
		else buffer[i]=0;
	}
	if (buffer == NULL) {
		printf("Error AX25");
		return -1;
	}
	write(3,buffer,size);
	printf("1 - %d 2 - %d 3 - %d\n",fd, buffer,size);
		
	return 0;
}
int test_lock() {
	return 0;
}
int test_query() {
	
	return 0;
}
int test_set(int delim_n) {	
	int fd;
	int ret;
	int four;
	four = 4;
	fd = open("/dev/afsk",O_WRONLY);
	if (fd < 0) {
		printf("Can't open device\n");
		return -1;
	}
	printf("%d\n", fd);
	ret = ioctl(fd, 6670, &four);
	printf("%d\n",ret);
	ret = ioctl(fd, 6669, &delim_n);
	printf("%d\n",ret);
	printf("%d\n",delim_n);
	return 0;	
}
