CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

rebuild: clean all

all: ac-matrice ac-hachage

ac-matrice: ac-matrice.o ac-matrice.h
	$(CC) -o ac-matrice ac-matrice.o $(LDFLAGS)

ac-matrice.o: ac-matrice.c
	$(CC) -c ac-matrice.c $(CFLAGS)

ac-hachage: ac-hachage.o ac-hachage.h
	$(CC) -o ac-hachage ac-hachage.o $(LDFLAGS)

ac-hachage.o: ac-hachage.c
	$(CC) -c ac-hachage.c $(CFLAGS)


clean:
	$(RM) -f *.o ac-matrice ac-hachage

