/*
 * Copyright (c) 2018 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>

int	 b64_ntop(u_char *, size_t, char *, size_t);

int
b64_ntop(u_char *src, size_t srclength, char *target, size_t target_size)
{
	int		 i, j;
	size_t		 expect_siz;
	uint32_t	 bit24;
	const char	 b64str[] =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	expect_siz = ((srclength + 2) / 3) * 4 + 1;

	if (target == NULL)
		return ((int)expect_siz);
	if (target_size < expect_siz)
		return (-1);

	for (i = 0, j = 0; i < srclength; i += 3) {
		bit24 = src[i] << 16;
		if (i + 1 < srclength)
			bit24 |= src[i + 1] << 8;
		if (i + 2 < srclength)
			bit24 |= src[i + 2];

		target[j++] = b64str[(bit24 & 0xfc0000) >> 18];
		target[j++] = b64str[(bit24 & 0x03f000) >> 12];
		if (i + 1 < srclength)
			target[j++] = b64str[(bit24 & 0x000fc0) >> 6];
		else
			target[j++] = '=';
		if (i + 2 < srclength)
			target[j++] = b64str[(bit24 & 0x00003f)];
		else
			target[j++] = '=';
	}
	target[j] = '\0';

	return j;
}
