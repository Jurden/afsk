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
#define QUERY_DELIM 6669
#define SET_DELIM 6670 
int test_afsk(char *callsign, char *data);
int test_lock();
int test_query();
int test_set(int delim_n);
void child_u(int fd);
void forkChild (int amount, int fd);


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
			if (ret != 0 ) {
				printf("ERROR\n");
				return -1;
			}
			return 0;
		case 2:
			if(argc != 2) {
				printf("Test doesn't require arg\n");
				return -1;
			}
			ret = test_lock();
			if (ret != 0 ) {
				printf("ERROR\n");
				return -1;
			}
			return 0;
		case 3:
			if(argc != 2) {
				printf("Test doesn't require arg\n");
				return -1;
			}
			ret = test_query();
			if (ret != 0 ) {
				printf("ERROR\n");
				return -1;
			}
			return 0;
		case 4:
			if(argc != 3) {
				printf("Include number of delims\n");
				return -1;
			}
			delim_cnt = atoi(argv[2]);
			if (ret != 0 ) {
				printf("ERROR\n");
				return -1;
			}
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
	for (i = 0; i < size*sizeof(uint8_t); i++) {
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
	printf("1 - %d 2 - %d 3 - %d\n",fd, data,size);
		
	return 0;
}
int test_lock() {
	int fd;
	int status = 0;
	pid_t wpid;

	fd = open("/dev/afsk",O_WRONLY);
	if (fd < 0) {
		printf("Can't open device\n");
		return -1;
	}

	forkChild(2, fd);
	while ((wpid = wait(&status)) > 0) {
	}
	
	return 0;
}
int test_query() {
	int fd;
	int ret;
	int delim = 0;
	fd = open("/dev/afsk",O_WRONLY);
	if (fd < 0) {
		printf("Can't open device\n");
		return -1;
	}
	ret = ioctl(fd, QUERY_DELIM, &delim);
	if (ret != 0) {
		printf("QUERY_DELIM ERROR");
		return -1;
	}
	printf("Delimiter count is %d\n", delim);
	return 0;
}
int test_set(int delim_n) {	
	int fd;
	int ret;
	int delim = 0;
	fd = open("/dev/afsk",O_WRONLY);
	if (fd < 0) {
		printf("Can't open device\n");
		return -1;
	}
	ret = ioctl(fd, SET_DELIM, &delim_n);
	if (ret != 0) {
		printf("SET_DELIM ERROR");
		return -1;
	}
	ret = ioctl(fd, QUERY_DELIM, &delim);
	if (ret != 0) {
		printf("QUERY_DELIM ERROR");
		return -1;
	}
	printf("Should be %d, Actually is %d\n",delim_n, delim);
	return 0;	
}
void forkChild (int amount, int fd)
{
	int i;
	pid_t pid;
	for(i = 1; i <= amount; i++) {
		pid = fork();
		if (pid == 0) {
			child_u(fd);
			break;
		}
	}
}

void child_u(int fd)
{
	int i, j;
	int set = 0, get;
	int ret;
	int size;
	char data[] = "locktest";
	size = strlen(data);
	for (i = 0; i < 10; i++) {
		//set = i;
		ret = write(fd, *data, size);
		if (ret != 0)
			printf("ioctl\n");
		else
			printf("Write #%d\n",i);
/*		ret = ioctl(fd, QUERY_DELIM, &get);
		if (ret != 0)
			printf("ioctl\n");
		else
			printf("Delim count is %d\n", get);*/
	}/*
	for (i=0; i<10; i++) {	
		ret = ioctl(fd, QUERY_DELIM, &get);
		if (ret != 0)
			printf("ioctl\n");
		else
			printf("Delim count is %d\n", get);
	}*/
}

