CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

BIN_DIR = bin

rebuild: clean all

all: $(BIN_DIR) ac-matrice ac-hachage

ac-matrice: $(BIN_DIR)/ac-matrice.o $(BIN_DIR)/trie_table.o
	$(CC) -o ac-matrice $(BIN_DIR)/trie_table.o $(BIN_DIR)/ac-matrice.o $(LDFLAGS)

$(BIN_DIR)/ac-matrice.o: ac-matrice.c
	$(CC) -c ac-matrice.c -o $@ $(CFLAGS)

$(BIN_DIR)/trie_table.o: Trie_Table/trie_table.c
	$(CC) -c Trie_Table/trie_table.c -o $@ $(CFLAGS)

ac-hachage: $(BIN_DIR)/ac-hachage.o $(BIN_DIR)/trie_hashtable.o
	$(CC) -o ac-hachage $(BIN_DIR)/trie_hashtable.o $(BIN_DIR)/ac-hachage.o $(LDFLAGS)

$(BIN_DIR)/ac-hachage.o: ac-hachage.c
	$(CC) -c ac-hachage.c -o $@ $(CFLAGS)

$(BIN_DIR)/trie_hashtable.o: Trie_Hashtable/trie_hashtable.c
	$(CC) -c Trie_Hashtable/trie_hashtable.c -o $@ $(CFLAGS)

$(BIN_DIR):
	mkdir $@

clean:
	$(RM) -f *.o ac-matrice ac-hachage
	rm -rf $(BIN_DIR)

