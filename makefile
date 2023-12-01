CC = gcc
CFLAGS = -std=c18 -Wpedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

BIN_DIR = bin

rebuild: clean all

all: $(BIN_DIR) ac-matrice ac-hachage genere-mots genere-texte

ac-matrice: $(BIN_DIR)/ac-matrice.o $(BIN_DIR)/trie_table.o $(BIN_DIR)/aho-corasick-table.o $(BIN_DIR)/queue.o $(BIN_DIR)/list.o
	$(CC) -o ac-matrice $(BIN_DIR)/queue.o $(BIN_DIR)/list.o $(BIN_DIR)/trie_table.o $(BIN_DIR)/aho-corasick-table.o $(BIN_DIR)/ac-matrice.o $(LDFLAGS)
	
$(BIN_DIR)/trie_table.o: Trie_Table/trie_table.c
	$(CC) -o $@ -c Trie_Table/trie_table.c $(CFLAGS)

$(BIN_DIR)/aho-corasick-table.o: Aho-Corasick/aho-corasick.c Trie_Table/trie_table.h Queue/queue.h List/list.h
	$(CC) -o $@ -c Aho-Corasick/aho-corasick.c $(CFLAGS) -DMATRICE

$(BIN_DIR)/ac-matrice.o: ac-matrice.c Aho-Corasick/aho-corasick.h
	$(CC) -o $@ -c ac-matrice.c $(CFLAGS) 



ac-hachage: $(BIN_DIR)/ac-hachage.o $(BIN_DIR)/trie_hashtable.o $(BIN_DIR)/aho-corasick-hashtable.o $(BIN_DIR)/queue.o $(BIN_DIR)/list.o
	$(CC) -o ac-hachage $(BIN_DIR)/queue.o $(BIN_DIR)/list.o $(BIN_DIR)/trie_hashtable.o $(BIN_DIR)/aho-corasick-hashtable.o $(BIN_DIR)/ac-hachage.o $(LDFLAGS)

$(BIN_DIR)/trie_hashtable.o: Trie_Hashtable/trie_hashtable.c
	$(CC) -o $@ -c Trie_Hashtable/trie_hashtable.c $(CFLAGS)

$(BIN_DIR)/aho-corasick-hashtable.o: Aho-Corasick/aho-corasick.c Trie_Hashtable/trie_hashtable.h Queue/queue.h List/list.h
	$(CC) -o $@ -c Aho-Corasick/aho-corasick.c $(CFLAGS)

$(BIN_DIR)/ac-hachage.o: ac-hachage.c Aho-Corasick/aho-corasick.h
	$(CC) -o $@ -c ac-hachage.c $(CFLAGS)




$(BIN_DIR)/queue.o: Queue/queue.c
	$(CC) -o $@ -c Queue/queue.c $(CFLAGS)

$(BIN_DIR)/list.o: List/list.c
	$(CC) -o $@ -c List/list.c $(CFLAGS)




genere-mots: $(BIN_DIR)/genere-mots.o 
	$(CC) -o genere-mots $(BIN_DIR)/genere-mots.o

$(BIN_DIR)/genere-mots.o: Gen/genere-mots.c
	$(CC) -o $@ -c Gen/genere-mots.c $(CFLAGS)



genere-texte: $(BIN_DIR)/genere-texte.o 
	$(CC) -o genere-texte $(BIN_DIR)/genere-texte.o

$(BIN_DIR)/genere-texte.o: Gen/genere-texte.c
	$(CC) -o $@ -c Gen/genere-texte.c $(CFLAGS)




$(BIN_DIR):
	mkdir $@




clean:
	$(RM) -f ac-matrice ac-hachage genere-mots genere-texte
	rm -rf $(BIN_DIR)
	rm -rf Texts
	rm result.txt

