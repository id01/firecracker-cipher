#include <stdio.h>
#include <stdlib.h>

#include "firecracker.h"

// Urandom
void urandom(uchar* output, int outputlen) {
	FILE* f_dev_urandom = fopen("/dev/urandom", "r");
	for (int i=0; i<outputlen; i++) {
		output[i] = fgetc(f_dev_urandom);
	}
	fclose(f_dev_urandom);
}

int main() {
	unsigned char * plaintext = "Attack at dawn.";
	unsigned char * ciphertext = malloc(16);
	unsigned char * decrypted = malloc(16);
	unsigned char * corrupted = malloc(16);
	unsigned char * wrongkey = malloc(16);
	unsigned char * key = "12345678123456781234567812345678";
	unsigned char * key2 = "12345678123456781234567812345679";
	unsigned char * seed = malloc(32); urandom(seed, 32);
	firecracker_encrypt(plaintext, 16, key, seed, ciphertext);
	firecracker_decrypt(ciphertext, 16, key, seed, decrypted); ciphertext[3] ^= 0x01;
	firecracker_decrypt(ciphertext, 16, key, seed, corrupted); ciphertext[3] ^= 0x01;
	firecracker_decrypt(ciphertext, 16, key2, seed, wrongkey);
	printf("Plaintext: ");
	for (int i=0; i<16; i++) {
		fputc(plaintext[i], stdout);
	}
	printf("\nCiphertext: ");
	for (int i=0; i<16; i++) {
		fputc(ciphertext[i], stdout);
	}
	printf("\nDecrypted: ");
	for (int i=0; i<16; i++) {
		fputc(decrypted[i], stdout);
	}
	printf("\nCorrupted: ");
	for (int i=0; i<16; i++) {
		fputc(corrupted[i], stdout);
	}
	printf("\nWith Wrong Key: ");
	for (int i=0; i<16; i++) {
		fputc(wrongkey[i], stdout);
	}
	printf("\nKey: ");
	for (int i=0; i<8; i++) {
		fputc(key[i], stdout);
	}
	printf("\nSeed: ");
	for (int i=0; i<8; i++) {
		fputc(seed[i], stdout);
	}
	puts("");
}
