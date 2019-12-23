all: main.c
	gcc -g -Wall -o eyTerminal main.c

clean: 
	$(RM) myprog
