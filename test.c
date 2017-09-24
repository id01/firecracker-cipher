#include <stdio.h>
#include <stdlib.h>

#include "firecracker.h"

unsigned char plaintext[] = "This is a message. A very, very long message. I think it is a multiple of 16. I am not sure. Don't be like me. Testing dynamite.";

// Urandom
void urandom(uchar* output, int outputlen) {
	FILE* f_dev_urandom = fopen("/dev/urandom", "r");
	for (int i=0; i<outputlen; i++) {
		output[i] = fgetc(f_dev_urandom);
	}
	fclose(f_dev_urandom);
}

int main() {
	unsigned char * ciphertext = malloc(sizeof(plaintext));
	unsigned char * decrypted = malloc(sizeof(plaintext));
	unsigned char * corrupted = malloc(sizeof(plaintext));
	unsigned char * wrongkey = malloc(sizeof(plaintext));
	unsigned char * ciphertext16 = malloc(sizeof(plaintext));
	unsigned char * decrypted16 = malloc(sizeof(plaintext));
	unsigned char * wrongkey16 = malloc(sizeof(plaintext));
	unsigned char * key1 = "12345678123456781234567812345678";
	unsigned char * key2 = "12345678123457781234567812345678";
	unsigned char * seed = malloc(32); urandom(seed, 32);
	firecracker_encrypt(plaintext, sizeof(plaintext)-1, key1, seed, ciphertext, 32);
	firecracker_decrypt(ciphertext, sizeof(plaintext)-1, key1, seed, decrypted, 32); ciphertext[23] ^= 0x01;
	firecracker_decrypt(ciphertext, sizeof(plaintext)-1, key1, seed, corrupted, 32); ciphertext[23] ^= 0x01;
	firecracker_decrypt(ciphertext, sizeof(plaintext)-1, key2, seed, wrongkey, 32);
	firecracker_encrypt(plaintext, sizeof(plaintext)-1, key1, seed, ciphertext16, 16);
	firecracker_decrypt(ciphertext16, sizeof(plaintext)-1, key1, seed, decrypted16, 16);
	firecracker_decrypt(ciphertext16, sizeof(plaintext)-1, key2, seed, wrongkey16, 16);
	printf("Sizeof(plaintext) without null: %lu\n", sizeof(plaintext)-1);
	printf("Plaintext: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(plaintext[i], stdout);
	}
	printf("\nCiphertext: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(ciphertext[i], stdout);
	}
	printf("\nDecrypted: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(decrypted[i], stdout);
	}
	printf("\nCorrupted: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(corrupted[i], stdout);
	}
	printf("\nWith Wrong Key: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(wrongkey[i], stdout);
	}
	printf("\nCiphertext16: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(ciphertext16[i], stdout);
	}
	printf("\nDecrypted16: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(decrypted16[i], stdout);
	}
	printf("\nWrongkey16: ");
	for (int i=0; i<sizeof(plaintext); i++) {
		fputc(wrongkey16[i], stdout);
	}
	printf("\nKey: ");
	for (int i=0; i<32; i++) {
		fputc(key1[i], stdout);
	}
	printf("\nSeed: ");
	for (int i=0; i<32; i++) {
		fputc(seed[i], stdout);
	}
	puts("");
}
