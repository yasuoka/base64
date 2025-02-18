/*
 * cc -o b64_pton_test b64_pton.c b64_pton_test.c
 * ./b64_pton_test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int      b64_pton(const char *, u_char *, size_t);

static int	outlen;
static u_char	outbuf[1024];

#define ASSERT(_cond)							\
	do {								\
		if (!(_cond)) {						\
			fprintf(stdout, 				\
			    "NG\nASSERT(%s) failed in %s():%s:%d",	\
			    #_cond, __func__, __FILE__, __LINE__);	\
			fflush(stdout);					\
			abort();					\
		}							\
	} while (0/*CONSTCOND*/)

#define TEST(_testfn)				\
	do {					\
		printf("%-24s ... ", #_testfn);	\
		fflush(stdout);			\
		_testfn();			\
		printf("ok\n");			\
	} while (0/*CONSTCOND*/)


static void
test_01(void)
{
	outlen = b64_pton("", outbuf, sizeof(outbuf));
	ASSERT(outlen == 0);
}

static void
test_02(void)
{
	outlen = b64_pton("aG9nZWhvZ2U=", outbuf, sizeof(outbuf));
	ASSERT(outlen == 8);
	ASSERT(memcmp(outbuf, "hogehoge", 8) == 0);
}

static void
test_03(void)
{
	outlen = b64_pton("aG9nZ\nWhvZ2U=", outbuf, sizeof(outbuf));
	ASSERT(outlen == 8);
	ASSERT(memcmp(outbuf, "hogehoge", 8) == 0);
}

static void
test_04(void)
{
	outlen = b64_pton("aG9nZ\nWhvZ2U=", NULL, 0);
	ASSERT(outlen == 8);
}

static void
test_05(void)
{
	outlen = b64_pton("MQ==", outbuf, sizeof(outbuf));
	ASSERT(outlen == 1);
	ASSERT(memcmp(outbuf, "1", 1) == 0);
}

static void
test_06(void)
{
	outlen = b64_pton("MTI=", outbuf, sizeof(outbuf));
	ASSERT(outlen == 2);
	ASSERT(memcmp(outbuf, "12", 2) == 0);
}

static void
test_07(void)
{
	outlen = b64_pton("MTIz", outbuf, sizeof(outbuf));
	ASSERT(outlen == 3);
	ASSERT(memcmp(outbuf, "123", 3) == 0);
}

static void
test_exact_size_buffer(void)
{
	int	ret;
	char	out[32];

	/*
	 * the problem originaly fixed by OpenBSD
	 * https://github.com/openbsd/src/commit/f5ee4dc2dc626bdaf183ad1537a8a18568914ea1
	 */
	/*
	 * the test case is taken from
	 * https://gitweb.dragonflybsd.org/dragonfly.git/commitdiff/3bf574a91d98898f33673d3b78fb3fe581c3c4e7
	 */
	ret = b64_pton("FCiWkKuhdRq3tMmtAt9CpchTTYMlIW3U3gJsavDNxZI=", out, sizeof(out));
	ASSERT(ret == 32);
}

int
main(int argc, char *argv[])
{
	TEST(test_01);
	TEST(test_02);
	TEST(test_03);
	TEST(test_04);
	TEST(test_05);
	TEST(test_06);
	TEST(test_07);
	TEST(test_exact_size_buffer);

	exit(EXIT_SUCCESS);
}
