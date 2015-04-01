SRC=window.c
OBJS=$(SRC:.c=.o)
RC=menu.rc
OBJS+=$(RC:.rc=.o)
PROG=menu.exe
CC=gcc
MENU=windres
CFLAGS=-Wall -O3
LDFLAGS=-mwindows
RM=rm


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.rc
	$(MENU) $(RC) $*.o

.PHONY : all
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(OBJS)