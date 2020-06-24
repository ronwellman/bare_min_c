# https://opensource.com/article/18/8/what-how-makefile
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html#Option-Summary
CFLAGS= -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings -Wfloat-equal -Waggregate-return -Winline -Wvla

# Samples that may require multithreading
LDLIBS= -pthread

# Samples that may require crypto
LDLIBS= -lcrypto

# Samples that may require math module
LDLIBS= -lm

# grab all files ending in c
SRCS := $(wildcard *.c)

# substitute all files ending with c with just their filename
BINS := $(SRCS:%.c=%)

# all and clean do not refer to actual files
.PHONY: all clean

# compile all to binaries
all: ${BINS}

# remove all binaries verbosely
clean: 
	rm -rvf *.o ${BINS}
