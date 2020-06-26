# https://www.gnu.org/software/make/manual/make.html
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
CC= gcc
CFLAGS= -std=c11 -Wall -Wextra -Wpedantic -Wwrite-strings
CFLAGS+= -Wfloat-equal -Waggregate-return -Winline -Wvla

# grab all files ending in c
SRCS := $(wildcard *.c)

# substitute all files ending with c with just their filename
BINS := $(SRCS:%.c=%)

# all and clean do not refer to actual files
.PHONY: all clean

# compile all to binaries
all: 01-basics1 01-basics2 01-basics3

01-basics3: 01-helper.c 01-helper.h

# remove all binaries verbosely
clean: 
	rm -rvf *.o ${BINS}
