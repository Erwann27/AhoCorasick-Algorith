#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie_Hashtable/trie_hashtable.h"
#include "Aho-Corasick/aho-corasick.h"

#define BUF_SIZE 128
#define MAX_TEXT_LENGTH 5000000


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "expected 2 arguments : a file path with words and a file path with a text\n");
        exit(EXIT_FAILURE);
    }

    // Récupération des arguments
    char *words_file_path = argv[1];
    char *text_file_path = argv[2];
    // Création Trie

    FILE *f = fopen(words_file_path, "r");
    if (f == NULL) {
        fprintf(stderr, "error on fopen\n");
        exit(EXIT_FAILURE);
    }
    size_t word_count = 0;
    char word[BUF_SIZE];
    char **words = malloc(BUF_SIZE * BUF_SIZE);
    if(words == NULL){
        exit(EXIT_FAILURE);
    }
    for(size_t i = 0; i < BUF_SIZE; i += 1){
        words[i] = malloc(BUF_SIZE);
        if(words[i] == NULL){
            for(size_t j = 0; j < i; j += 1){
                free(words[j]);
            }
            free(words);
            exit(EXIT_FAILURE);
        }
    }

    while(fgets((char *) word, BUF_SIZE, f) != NULL) {
        strncpy(words[word_count], (char *)word, strlen(word) - 1);  
        ++word_count;
    }
          

    if (fclose(f) != 0) {
      fprintf(stderr, "Error on closing words file\n");
      exit(EXIT_FAILURE);
    }

    // // Récupération contenu du fichier texte
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
    // // Appel de Aho-Corasick sur les paramètres et récupération du nombre d'occurrences
    size_t occ_count = aho_corasick(words, word_count, (unsigned char *)text, strlen(text));

    // Affichage du nombre d'occurrences
    // printf("nombre d'occurrences de l'ensemble des mots de %s dans %s : %zu\n",
    //   word, text, occ_count);
    printf("%zu\n", occ_count);

    return EXIT_SUCCESS;
}
