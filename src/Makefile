# https://www.gnu.org/software/make/manual/make.html
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
CC= gcc
CFLAGS= -g -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings
CFLAGS+= -Wfloat-equal -Waggregate-return -Winline -Wvla
LDLIBS= -pthread

# grab all files ending in c
SRCS := $(wildcard *.c)

# substitute all files ending with c with just their filename
BINS := $(SRCS:%.c=%)

# all and clean do not refer to actual files
.PHONY: all clean

# compile all to binaries
all: 01-basics1 01-basics2 01-basics3 02-integer-32bit \
	02-integer-64bit 02-character1 02-float1 \
	02-xor 02-array1 02-array2 02-pointers1 \
	02-dynamic1 03-if 04-cli1 04-cli2 \
	05-struct1 06-file1 06-file2 \
	06-file3 07-concurrency1 07-concurrency2 \
	07-concurrency3 08-network1_server \
	09-queue 09-ll 09-stack
	

01-basics3: 01-helper.c 01-helper.h

05-struct1: 05-player.c 05-player.h

02-integer-32bit:
	${CC} ${CFLAGS} -m32 -o 02-integer-32bit 02-integer-32bit.c

07-concurrency2: 07-concurrency2.c 09-queue.h 09-queue.c

07-concurrency3: 07-concurrency3.c 09-queue.h 09-queue.c

09-queue: 09-queue_test.c 09-queue.c 09-queue.h

09-ll: 09-ll_test.c 09-ll.c 09-ll.h

09-stack: 09-stack_test.c 09-stack.c 09-stack.h

# remove all binaries verbosely
clean:
	rm -rvf *.o ${BINS}
