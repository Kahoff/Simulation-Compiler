OBJS = compiler.o parseTable.o 
CC = gcc
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)
FILENAME = compiler

$(FILENAME) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(FILENAME)

compiler.o : parseTable.h parseTable.c 
	$(CC) $(CFLAGS) compiler.c

parseTable.o : parseTable.h   
	$(CC) $(CFLAGS) parseTable.c

clean:
	del *.o  *~ $(FILENAME).exe
