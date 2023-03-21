/*-
 * Copyright (c) 2023, Collin Funk
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdint.h>
#include <stddef.h>

#include "arc4.h"

#define ARC4_SWAP(a, b) do { \
	uint8_t temp = (a); \
	(a) = (b); \
	(b) = temp; \
} while (0)

void
arc4_setkey(struct arc4_ctx *ctx, const uint8_t *key, uint32_t keylen)
{
	uint32_t i;
	uint8_t x;
	uint8_t y;

	for (i = 0; i < 256; ++i)
		ctx->data[i] = i;

	x = 0;
	y = 0;

	for (i = 0; i < 256; ++i) {
		/* y = (y + S[i] + key[i mod keylen]) mod 256 */
		y = (y + key[x] + ctx->data[i]) & 0xff;
		ARC4_SWAP(ctx->data[i], ctx->data[y]);
		x = (x + 1) % keylen;
	}

	ctx->x = 0;
	ctx->y = 0;
}

void
arc4_crypt(struct arc4_ctx *ctx, size_t len, const uint8_t *src, uint8_t *dest)
{
	size_t i;

	for (i = 0; i < len; ++i) {
		ctx->x = (ctx->x + 1) & 0xff;
		ctx->y = (ctx->y + ctx->data[ctx->x]) & 0xff;
		ARC4_SWAP(ctx->data[ctx->x], ctx->data[ctx->y]);
		dest[i] = src[i] ^
			ctx->data[(ctx->data[ctx->x] +
					ctx->data[ctx->y]) & 0xff];
	}
}

