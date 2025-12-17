# CHAPITRE 1 : BUT FINAL

but : game

# CHAPITRE 2 : VARIABLES

OFILES = main.o \
        outils.o \
	 	menu.o \
		options.o \
		regles.o \
		partie.o \
		robot.o

CC = gcc

CFLAGS = -Wall -ansi -pedantic

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

menu.o : menu.h

main.o : outils.h

outils.o : outils.h

options.o : options.h

regles.o : regles.h

partie.o : partie.h

robot.o : robot.h

# CHAPITRE 4 : DEPENDANCES AVEC COMMANDES

game : $(OFILES)
	$(CC) $(CFLAGS) -o game $(OFILES) -lgraph

# CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES

clean :
	-rm -f $(OFILES) game

# CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean

run :
	./game

