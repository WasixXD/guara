CC = gcc
CFLAGS = -Wextra -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g

all: run exec clean

run:
	$(CC) -o main.o src/*.c $(CFLAGS) 

exec: run
	./script.sh

clean: exec
	rm ./main.o

