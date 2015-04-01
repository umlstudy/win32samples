SRC=ex2.c
OBJS=$(SRC:.c=.o)
PROG=ex2.exe
CC=gcc
CFLAGS=-Wall -O3
LDFLAGS=-mwindows
RM=rm


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : all
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

.PHONY : clean
clean:
	$(RM) $(OBJS)