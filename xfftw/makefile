.SUFFIXES:.c .o

CC=gcc

CPPFLAGS=-I D:\Programs\windows_x64\xnl
SRCS=<add sourcefiles here>

OBJS=$(SRCS:.c=.o)

EXEC=<type target here>

start: $(OBJS)
	$(CC) $(CPPFLAGS) -shared -o $(EXEC) $(OBJS) -fPIC

.c.o:
	$(CC) -fPIC -Wall -o $@ -c $<

clean:
	rm -rf $(EXEC) $(OBJS)
