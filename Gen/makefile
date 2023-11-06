CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

all: genere-texte genere-mots

genere-texte: genere-texte.c genere-texte.o
	$(CC) -o genere-texte genere-texte.o $(LDFLAGS)

genere-texte.o: genere-texte.c
	$(CC) -c genere-texte.c $(CFLAGS)

genere-mots: genere-mots.c genere-mots.o
	$(CC) -o genere-mots genere-mots.o $(LDFLAGS)

genere-mots.o: genere-mots.c
	$(CC) -c genere-mots.c $(CFLAGS)

clean:
	$(RM) -f *.o genere-texte genere-mots


