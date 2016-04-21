#ifndef ENCODER_H
#define ENCODER_H
typedef struct data {
	int size;
	int *bits;
	int *stuffbits;
	int numbits;
	char *input;
	char *encode;
} data;
void encode(
	data *s,
	int mode
	);
void S_OR_M(
	int sm
	);
#endif
