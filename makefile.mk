#Do not edit the contents of this file.
CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = 201490550_a04 201490550_a04
OBJFILES = 201490550_a04.o

all:
	rm -f $(OBJFILES) $(TARGET) *~ 
	make $(TARGET)

201490550_a04: 201490550_a04.c
	$(CC) $(CFLAGS) -o 201490550_a04 201490550_a04.c $(LDFLAGS)

test1: 201490550_a04
	./201490550_a04 10 10 10 10
test2: 201490550_a04
	./201490550_a04 5 5 5 5
	
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
