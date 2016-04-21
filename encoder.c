// Jordan Millett ECE 331 
#include "encoder.h"
#include <stdio.h>
#include <stdlib.h>

void encode(data *s, int mode)
{
// Init
	int i;
	int j;
	int sm = 1;
	int counter = 0;
	int stuffed = 0;
	int MASK = 1;
	s->numbits = (s->size * 8);
	
	s->bits = (int *) malloc(4096);
	s->stuffbits = (int *) malloc(4096);
	s->encode = (char *) malloc(4096);

// Binary conversion
	for (i = 0; i < s->size; i++) {
	// For each character
		for (j = 0; j < 8; j++){
		// For the 8 bits
				if((s->input[i]) & (MASK << j)) {
					s->bits[(i * 8) + j] = 1;
				} else {
					s->bits[(i * 8) + j] = 0;
				}
				// Convert to binary
		}
	}
	
// Bit stuffing
	if (mode) {
		for (i = 0; i < s->numbits; i++) {
			s->stuffbits[i+stuffed] = s->bits[i];
			if(s->stuffbits[i+stuffed]) {
				counter++;
				if(counter == 5) {
					stuffed++;
					counter = 0;
					s->numbits++;
					s->stuffbits[i+stuffed] = 0;
				}
			} else {
				counter = 0;
			}
		}
	}
// Printing 
	S_OR_M(sm);
	for (i = 0; i < s->numbits; i++) {
		if(s->stuffbits[i] == 1) {
			S_OR_M(sm);
		} else {
			sm *= -1;
			S_OR_M(sm);
		}
		if(!(i%8-6)){
			printf(" ");
		}
	}
	printf("\n");
	free(s->bits);
	free(s->stuffbits);
	free(s->encode);	
}

void S_OR_M(int sm) {
	if(sm == 1) {
		printf("S ");
	} else {
		printf("M ");
	}
}
