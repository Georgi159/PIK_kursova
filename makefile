exec.out : kursova.o analysis.o menu.o
	gcc -std=c11 -Wall -pedantic  -o exec.out kursova.o analysis.o menu.o  -O2 -lcurses -lmenu 

kursova.o : kursova.c
	gcc -std=c11 -Wall -pedantic   kursova.c -c -o kursova.o -O2 -lcurses -lmenu 

analysis.o : analysis.c
	gcc -std=c11 -Wall -pedantic   analysis.c -c -o analysis.o  -O2 -lcurses

menu.o : menu.c
	gcc -std=c11 -Wall -pedantic   menu.c -c -o menu.o  -O2 -lcurses

clean: 
	rm -f *.o exec.out