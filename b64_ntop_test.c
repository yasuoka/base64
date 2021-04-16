/*
 * cc -o b64_ntop_test b64_ntop.c b64_ntop_test.c
 * ./b64_ntop_test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
		printf("%s ... ", #_testfn);	\
		fflush(stdout);			\
		_testfn();			\
		printf("ok\n");			\
	} while (0/*CONSTCOND*/)

int b64_ntop(u_char *, size_t, char *, size_t);

static void test_01(void);

static void
test_01(void)
{
	char	buf[80];

	b64_ntop((u_char *)"hogehoge", 8, buf, sizeof(buf));
	ASSERT(strcmp(buf, "aG9nZWhvZ2U=") == 0);
}

#define RFC4648_TEST(_n, _in, _expect)				\
static void							\
rfc4648_ ## _n(void)						\
{								\
	char buf[80];						\
	b64_ntop((u_char *)(_in), strlen((_in)), buf, sizeof(buf));	\
	ASSERT(strcmp(buf, (_expect)) == 0);			\
}
RFC4648_TEST(1, "", "")
RFC4648_TEST(2, "f", "Zg==")
RFC4648_TEST(3, "fo", "Zm8=")
RFC4648_TEST(4, "foo", "Zm9v")
RFC4648_TEST(5, "foob", "Zm9vYg==")
RFC4648_TEST(6, "fooba", "Zm9vYmE=")
RFC4648_TEST(7, "foobar", "Zm9vYmFy")

int
main(int argc, char *argv[])
{
	TEST(test_01);
	TEST(rfc4648_1);
	TEST(rfc4648_2);
	TEST(rfc4648_3);
	TEST(rfc4648_4);
	TEST(rfc4648_5);
	TEST(rfc4648_6);
	TEST(rfc4648_7);

	exit(EXIT_SUCCESS);
}
