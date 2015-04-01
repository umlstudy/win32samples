
SRC=ex.c
#OBJS=$(SRC:.c=.o)
OBJS=ex.o exres.o
PROG=ex.exe
CC=gcc
RC=windres
CFLAGS=-Wall -O3
LDFLAGS=-mwindows
RM=del

%.o: %.rc
	$(RC) -o $@ $<
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm *.o
#	$(RM) $(OBJS)