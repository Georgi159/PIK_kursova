exec.out : kursova.o 
	gcc -std=c11 -Wall -pedantic  -o exec.out kursova.o

kursova.o : kursova.c
	gcc -std=c11 -Wall -pedantic   kursova.c -c -o kursova.o

clean: 
	rm -f *.o exec.out