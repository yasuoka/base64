

test:
	cc -std=c99 -Wall -Wextra -Wno-unused-parameter \
	    -o b64_pton_test b64_pton_test.c b64_pton.c
	./b64_pton_test

clean:
	rm -f *.o b64_pton_test *.core
