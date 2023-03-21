
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "arc4.h"

int
main(void)
{
	size_t i;
	struct arc4_ctx ctx;
	uint8_t buffer1[50];

	/*
	 * See:
	 * https://datatracker.ietf.org/doc/html/draft-kaukonen-cipher-arcfour-03
	 * More test vectors, this one is credited to the US Department of 
	 * Commerce.
	 */
	uint8_t test_plaintext[] = {0xdc, 0xee, 0x4c, 0xf9, 0x2c};
	uint8_t test_key[] = {0x61, 0x8a, 0x63, 0xd2, 0xfb};
	uint8_t test_ciphertext[] = {0xf1, 0x38, 0x29, 0xc9, 0xde};

	memset(buffer1, 0, 50);
	arc4_setkey(&ctx, test_key, sizeof(test_key));
	arc4_crypt(&ctx, sizeof(test_plaintext), test_plaintext, buffer1);

	if (memcmp(buffer1, test_ciphertext, sizeof(test_ciphertext)) != 0) {
		printf("Failed.\n");
		printf("ctx.data[]:\n");
		for (i = 0; i < sizeof(test_ciphertext); ++i)
			printf("0x%02x ", buffer1[i]);

		printf("\ntest_ciphertext[]:\n");
		for (i = 0; i < sizeof(test_ciphertext); ++i)
			printf("0x%02x ", test_ciphertext[i]);

		printf("\ncomputed ciphertext[]:\n");
		for (i = 0; i < sizeof(test_ciphertext); ++i)
			printf("0x%02x ", buffer1[i]);

		printf("\n");
		exit(1);
	}

	printf("Passed.\n");
	printf("test_ciphertext[]:\n");
	for (i = 0; i < sizeof(test_ciphertext); ++i)
			printf("0x%02x ", test_ciphertext[i]);

	printf("\ncomputed ciphertext[]:\n");
	for (i = 0; i < sizeof(test_ciphertext); ++i)
			printf("0x%02x ", buffer1[i]);

	printf("\n");
	return 0;
}

