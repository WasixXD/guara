CC = g++
CFLAGS =  -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c++20


.PHONY: all build run clean

all: build run clean

build: 
	clear
	$(CC)  -o guara src/* $(CFLAGS) 

run: build
	./guara

clean: run 