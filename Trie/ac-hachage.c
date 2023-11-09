#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "ac-hachage.h"
#include "../Aho-Corasick/aho_corasick.c"

#define DEF_VALUE NULL
#define MAX_NODE 100
#define BUF_SIZE 128
#define MAX_TEXT_LENGTH 5000000

int hashFun(int node, unsigned char transition, Trie t);

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
        fprintf(stderr, "Erreur malloc");
        exit(EXIT_FAILURE);
    }
    t->maxNode = maxNode;
    t->nextNode = 1;
    t->transition = malloc((size_t)(maxNode) * sizeof(List *));
    if(t->transition == NULL){
        fprintf(stderr, "Erreur allocation transition\n");
        return NULL;
    }
    t->finite = malloc((size_t)maxNode * sizeof(int));
    if(t->finite == NULL){
        free(t->transition);
        fprintf(stderr, "Erreur allocation finite\n");
        return NULL;
    }
    for(int i = 0; i < maxNode * (1 / FILL_RATE); i += 1){
        t->transition[i] = DEF_VALUE;
    }
    return t;
}

void insertInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return;
    }
    // printf("Insertion de : %s\n", w);
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        // printf("Noeud courrant : %d\n", currentNode);
        int hashPosition = hashFun(currentNode, w[i], trie);
        // printf("Postion table hachage : %d\n", hashPosition);

        // LA FONCTION DE HACHAGE NOUS RENVOIE UNE POSITION OU AUCUNE
        // LISTE N'EST INITIALISEE
        if(trie->transition[hashPosition] == NULL){
            List list = malloc(sizeof(List));
            if(list == NULL){
                fprintf(stderr, "Erreur allocation list\n");
                return;
            }
            list->startNode = currentNode;
            list->letter = w[i];
            list->targetNode = trie->nextNode;
            list->next = NULL;
            trie->transition[hashPosition] = list;
            currentNode = trie->nextNode;
            trie->nextNode += 1;
        }
        else {
            List list = trie->transition[hashPosition];
            while (list->next != NULL && list->letter != w[i] 
                && list->startNode != currentNode){
                list = list->next;                
            }
            // LA LISTE OBTENUE AVEC LA FONCTION DE HACHAGE NE CONTIENT
            // PAS LE NOEUD SOUHAITE
            if(list->next == NULL && list->startNode != currentNode){
                List nextListe = malloc(sizeof(List));
                if(nextListe == NULL){
                    fprintf(stderr, "Erreur allocation list\n");
                    return;
                }
                list->next = nextListe;
                nextListe->startNode = currentNode;
                nextListe->letter = w[i];
                nextListe->targetNode = trie->nextNode;
                currentNode = trie->nextNode;
                trie->nextNode += 1;
            }

            // LA LISTE OBTENUE CONTIENT LE NOEUD SOUHAITE
            else {
                // printf("J'ai trouve la lettre %c\n", list->letter);
                currentNode = list->targetNode;
            }
        }
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
        int hashPosition = hashFun(currentNode, w[i], trie);
        if(trie->transition[hashPosition] == NULL){
            return 0;
        }
        List list = trie->transition[hashPosition];
        while (list->next != NULL && list->letter != w[i] 
                && list->startNode != currentNode){
            list = list->next;
        }
        if(list->letter != w[i] && list->startNode != currentNode){
            return 0;
        }
        currentNode = list->targetNode;
    }
    if(trie->finite[currentNode]){
        return 1;
    }
    return 0;
}

int hashFun(int node, unsigned char transition, Trie t){
    return(node * 17 + transition * 13) % (int)(t->maxNode * FILL_RATE);
}
