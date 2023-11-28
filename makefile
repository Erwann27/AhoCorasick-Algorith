CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

BIN_DIR = bin

rebuild: clean all

all: $(BIN_DIR) ac-matrice

ac-matrice: $(BIN_DIR)/ac-matrice.o $(BIN_DIR)/trie_table.o $(BIN_DIR)/aho-corasick-table.o $(BIN_DIR)/queue.o $(BIN_DIR)/list.o
	$(CC) -o ac-matrice $(BIN_DIR)/queue.o $(BIN_DIR)/list.o $(BIN_DIR)/trie_table.o $(BIN_DIR)/aho-corasick-table.o $(BIN_DIR)/ac-matrice.o $(LDFLAGS)
	
$(BIN_DIR)/trie_table.o: Trie_Table/trie_table.c
	$(CC) -o $@ -c Trie_Table/trie_table.c $(CFLAGS)

$(BIN_DIR)/queue.o: Queue/queue.c
	$(CC) -o $@ -c Queue/queue.c $(CFLAGS)

$(BIN_DIR)/list.o: List/list.c
	$(CC) -o $@ -c List/list.c $(CFLAGS)

$(BIN_DIR)/aho-corasick-table.o: Aho-Corasick/aho-corasick.c Trie_Table/trie_table.h Queue/queue.h List/list.h
	$(CC) -o $@ -c Aho-Corasick/aho-corasick.c $(CFLAGS)

$(BIN_DIR)/ac-matrice.o: ac-matrice.c Aho-Corasick/aho-corasick.h
	$(CC) -o $@ -c ac-matrice.c $(CFLAGS)



# ac-hachage: $(BIN_DIR)/ac-hachage.o $(BIN_DIR)/trie_hashtable.o
# 	$(CC) -o ac-hachage $(BIN_DIR)/trie_hashtable.o $(BIN_DIR)/ac-hachage.o $(LDFLAGS)

# $(BIN_DIR)/ac-hachage.o: ac-hachage.c
# 	$(CC) -o $@ -c ac-hachage.c $(CFLAGS)

# $(BIN_DIR)/trie_hashtable.o: Trie_Hashtable/trie_hashtable.c
# 	$(CC) -o $@ -c Trie_Hashtable/trie_hashtable.c $(CFLAGS)




$(BIN_DIR):
	mkdir $@

clean:
	$(RM) -f *.o ac-matrice ac-hachage
	rm -rf $(BIN_DIR)

