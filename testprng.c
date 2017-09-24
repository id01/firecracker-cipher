#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "firecracker.h"
#define PRNGBYTES 32

// Urandom
void urandom(uchar* output, int outputlen) {
	FILE* f_dev_urandom = fopen("/dev/urandom", "r");
	for (int i=0; i<outputlen; i++) {
		output[i] = fgetc(f_dev_urandom);
	}
	fclose(f_dev_urandom);
}

int main() {
	uint64_t* s = malloc(PRNGBYTES);
	uint64_t* out = malloc(8);
	urandom((uchar*)s, PRNGBYTES);
	firecracker_prng_struct* prng = malloc(PRNGBYTES+4);
	firecracker_prng_struct_init(prng, PRNGBYTES/8);
	firecracker_seed(prng, s);
	for (int i=0; i<4096; i++) {
		*out = firecracker_rand(prng);
		fputc(((uchar*)out)[0], stdout);
		fputc(((uchar*)out)[1], stdout);
		fputc(((uchar*)out)[2], stdout);
		fputc(((uchar*)out)[3], stdout);
	}
}
