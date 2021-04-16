CFLAGS=	-Wall -Wextra -Wno-unused-parameter -Wno-sign-compare

test:
	cc ${CFLAGS} -o b64_ntop_test b64_ntop_test.c b64_ntop.c
	./b64_ntop_test
	cc ${CFLAGS} -o b64_pton_test b64_pton_test.c b64_pton.c
	./b64_pton_test

clean:
	rm -f *.o b64_pton_test *.core
