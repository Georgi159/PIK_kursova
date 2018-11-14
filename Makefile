CC=gcc 
CPPFLAGS=-Wall -pedantic -Wextra  -O2
LDLIBS=-lhpdf
OBJDIR=obj
SRC=src

all : exec.out

exec.out : $(OBJDIR)/kursova.o $(OBJDIR)/analysis.o $(OBJDIR)/menu.o $(OBJDIR)/getch.o $(OBJDIR)
	$(CC) $(CFLAGS)   $(CPPFLAGS)  $(OBJDIR)/kursova.o $(OBJDIR)/analysis.o $(OBJDIR)/menu.o $(OBJDIR)/getch.o   -o exec.out

$(OBJDIR)/%.o:  $(SRC)/%.c $(OBJDIR)
	$(CC) $(CFLAGS)  $(CPPFLAGS) -c $< -o $@ 

# $(OBJDIR)/kursova.o : $(SRC)/kursova.c $(OBJDIR)
# 	$(CC) $(CFLAGS) $(CPPFLAGS)   $(SRC)/kursova.c -c -o $(OBJDIR)/$@

# $(OBJDIR)/analysis.o : $(SRC)/analysis.c $(OBJDIR)
# 	$(CC) $(CFLAGS) $(CPPFLAGS)   $(SRC)/analysis.c -c -o $(OBJDIR)/$@

# $(OBJDIR)/menu.o : $(SRC)/menu.c $(OBJDIR)
# 	$(CC) $(CFLAGS) $(CPPFLAGS)   $(SRC)/menu.c -c -o $(OBJDIR)/$@

# $(OBJDIR)/getch.o : $(SRC)/getch.c $(OBJDIR)
# 	$(CC) $(CFLAGS) $(CPPFLAGS)   $(SRC)/getch.c -c -o $(OBJDIR)/$@

$(OBJDIR) : 
	mkdir -p $(OBJDIR)

clean: 
	rm -f *.o exec.out
	rm -rf $(OBJDIR)



.PHONY: all exec.out clean
