CC = gcc
CFLAGS = -g
RM = rm -f

default: all
all: HelloWorld Fibonacci shell

HelloWorld: HelloWorld.c 
	$(CC) $(CFLAGS) -o HelloWorld HelloWorld.c

fib2: fib2.c 
	$(CC) $(CFLAGS) -o Fibonacci Fibonacci.c

shelly: shelly.c
	$(CC) $(CFLAGS) -o shell shell.c

clean veryclean:
	$(RM) HelloWorld Fibonacci shell
