exec.out : kursova.o analysis.o menu.o
	gcc -std=c11 -Wall -pedantic  -o exec.out kursova.o analysis.o menu.o  -O2 

kursova.o : kursova.c
	gcc -std=c11 -Wall -pedantic   kursova.c -c -o kursova.o -O2 

analysis.o : analysis.c
	gcc -std=c11 -Wall -pedantic   analysis.c -c -o analysis.o  -O2 

menu.o : menu.c
	gcc -std=c11 -Wall -pedantic   menu.c -c -o menu.o  -O2 

clean: 
	rm -f *.o exec.out