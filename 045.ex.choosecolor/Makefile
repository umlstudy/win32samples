
SRC=ex.cc
#OBJS=$(SRC:.c=.o)
#OBJS=ex.o exres.o
OBJS=ex.o exres.o MessageToString.o
CC=gcc
PROG=ex.exe
RC=windres
CFLAGS=-ansi -std=c++98 -Wall -O3
LDFLAGS=-mwindows -lstdc++ 
RM=del

%.o: %.rc
	$(RC) -o $@ $<
	
%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm *.o
#	$(RM) $(OBJS)