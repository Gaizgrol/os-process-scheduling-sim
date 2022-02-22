OBJS	= main.o process.o
SOURCE	= main.c process.c
HEADER	= 
OUT		= scheduling-sim
CC	 	= gcc
FLAGS	= -g -c -Wall
LFLAGS	= 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c17


clean:
	rm -f $(OBJS)
