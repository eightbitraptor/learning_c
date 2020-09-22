CC=clang

optflags=-O0
warnflags=-Wall -Werror
debugflags=-g

cflags= $(debugflags) $(optflags) $(warnflags)

arrays: arrays.c
	$(CC) $(cflags) -o arrays arrays.c

single_list: single_list.c
	$(CC) $(cflags) -o single_list single_list.c
