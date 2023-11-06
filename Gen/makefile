CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm
FILES_PATH = ../Texts/*.txt

all: genV1 genV2

genV1: genV1.c genV1.o
	$(CC) -o genV1 genV1.o $(LDFLAGS)

genV1.o: genV1.c
	$(CC) -c genV1.c $(CFLAGS)

genV2: genV2.c genV2.o
	$(CC) -o genV2 genV2.o $(LDFLAGS)

genV2.o: genV2.c
	$(CC) -c genV2.c $(CFLAGS)

clean:
	$(RM) -f *.o genV1 genV2 $(FILES_PATH)


