OBJS	= tree.o
SOURCE	= tree.c
HEADER	= 
OUT	= tree
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

tree.o: tree.c
	$(CC) $(FLAGS) tree.c 


clean:
	rm -f $(OBJS) $(OUT)
