#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "ac-matrice.h"
#include "../Aho-Corasick/aho-corasick.c"

#define DEF_VALUE -1
#define MAX_NODE 100
#define BUF_SIZE 128
#define MAX_TEXT_LENGTH 5000000

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "expected 2 arguments : a file path with words and a file path with a text");
        exit(EXIT_FAILURE);
    }

    // Récupération des arguments
    char *words_file_path = argv[1];
    char *text_file_path = argv[2];
    text_file_path = text_file_path;
    // Création Trie

    Trie trie = createTrie(MAX_NODE);


    // Remplissage Trie avec les mots dans fichier de mots

    FILE *f = fopen(words_file_path, "r");
    if (f == NULL) {
        fprintf(stderr, "error on fopen\n");
        exit(EXIT_FAILURE);
    }
    size_t word_count = 0;
    unsigned char word[BUF_SIZE];
    while(fgets((char *) word, BUF_SIZE, f) != NULL) {
        word[strcspn((char *)word, "\n")] = 0;
        insertInTrie(trie, word);
        ++word_count;
    }
    if (fclose(f) != 0) {
      fprintf(stderr, "Error on closing words file\n");
      exit(EXIT_FAILURE);
    }

    // Récupération contenu du fichier texte
    f = fopen(text_file_path, "r");
    if (f == NULL) {
      fprintf(stderr, "error on fopen\n");
      exit(EXIT_FAILURE);
    }

    char text[MAX_TEXT_LENGTH];
    while(fgets((char *) word, BUF_SIZE, f) != NULL) {
        strcpy(text + strlen(text), (char *)word);
    }
    if (fclose(f) != 0) {
      fprintf(stderr, "Error on closing words file\n");
      exit(EXIT_FAILURE);
    }
    // Appel de Aho-Corasick sur les paramètres et récupération du nombre d'occurrences
    size_t occ_count = aho_corasick(trie, word_count, text, strlen(text));
    // Affichage du nombre d'occurrences
    printf("nombre d'occurrences de l'ensemble des mots de %s dans %s : %zu\n",
          word, text, occ_count);
    return EXIT_SUCCESS;
}

Trie createTrie(int maxNode){
    Trie t = malloc(sizeof(struct _trie));
    if(t == NULL){
        fprintf(stderr, "Erreur allocation\n");
        return NULL;
    }
    t->maxNode = maxNode;
    t->nextNode = 1;
    t->transition = malloc((size_t)(maxNode) * sizeof(int*));
    if(t->transition == NULL){
        fprintf(stderr, "Erreur allocation tableau\n");
        return NULL;
    }
    t->finite = malloc((size_t)maxNode * sizeof(int));
    if(t->finite == NULL){
        free(t->transition);
        fprintf(stderr, "Erreur allocation finite\n");
    }

    for(int i = 0; i < maxNode; i += 1){
        t->transition[i] = malloc(UCHAR_MAX * sizeof(int));
        if(t->transition[i] == NULL){
            fprintf(stderr, "Erreur allocation cellule tableau\n");
            for(int j = 0; j < i; j += 1){
                free(t->transition[j]);
            }
            return NULL;
        }
        for(int j = 0; j < UCHAR_MAX; j += 1){
            t->transition[i][j] = DEF_VALUE;
        }
    }
    return t;
}

void insertInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return;
    }
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        if(trie->transition[currentNode][w[i]] == -1){
            trie->transition[currentNode][w[i]] = trie->nextNode;
            trie->nextNode += 1;
        }
        currentNode = trie->transition[currentNode][w[i]];
    }
    trie->finite[currentNode] = 1;
}

int isInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return -1;
    }
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        if(trie->transition[currentNode][w[i]] == -1){
            return 0;
        }
        currentNode = trie->transition[currentNode][w[i]];
    }
    if(trie->finite[currentNode]){
        return 1;
    }
    return 0;
}

void print_trie(Trie t){
    for(int i = 0; i < t->maxNode; i += 1){
        printf("|");
        for(int j = 0; j < UCHAR_MAX; j += 1){
            printf("%d|", t->transition[i][j]);
        }
        printf("\n");
    }
}

void dispose_trie(Trie t){
    for(int i = 0; i < t->maxNode; i += 1){
        if(t->transition[i] != NULL){
            free(t->transition[i]);
        }
    }
}

