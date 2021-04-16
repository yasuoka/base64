/*
 * Copyright (c) 2016, 2017 YASUOKA Masahiko <yasuoka@yasuoka.net>
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
#include <ctype.h>

int	 b64_pton(const char *, u_char *, size_t);

int
b64_pton(const char *src, u_char *dst, size_t dstsiz)
{
	int		 i, j, k;
	uint32_t	 val3 = 0;
	const char	 b64_tbl[] =
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x3e\xff\xff\xff\x3f"
	    "\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\xff\xff\xff\x00\xff\xff"
	    "\xff\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e"
	    "\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\xff\xff\xff\xff\xff"
	    "\xff\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25\x26\x27\x28"
	    "\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	    "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";

	for (i = j = k = 0; src[i] != '\0'; i++) {
		if (isspace(src[i]))
			continue;
		if (b64_tbl[(u_char)src[i]] == (char)0xff)
			return(-1);
		val3 |= b64_tbl[(u_char)src[i]];
		if (src[i] != '=') {
			if (dst != NULL && k >= (ssize_t)dstsiz)
				return (-1);
			if (j % 4 == 1) {
				if (dst != NULL)
					dst[k] = val3 >> 4;
				k++;
			} else if (j % 4 == 2) {
				if (dst != NULL)
					dst[k] = val3 >> 2;
				k++;
			} else if (j % 4 == 3) {
				if (dst != NULL)
					dst[k] = val3;
				k++;
			}
		}
		val3 <<= 6;
		j++;
	}
	if (j % 4 != 0)
		return (-1);

	return (k);
}
