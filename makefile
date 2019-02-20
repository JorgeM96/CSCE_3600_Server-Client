CC=gcc
CFLAGS= -g
all:	svr	cli

svr: major2svr.c
	$(CC) -o svr $(CFLAGS) major2svr.c -lpthread
	
cli: major2cli.c
	$(CC) -o cli $(CFLAGS) major2cli.c -lpthread
clean:
	$(RM) cli svr
