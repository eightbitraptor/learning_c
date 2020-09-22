CC=clang

optflags=-O0
warnflags=-Wall -Werror
debugflags=-g

cflags= $(debugflags) $(optflags) $(warnflags)

arrays: arrays.c
	$(CC) $(cflags) -o arrays arrays.c
