#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
#ifdef TEXT_GEN
    if(argc != 3){
        fprintf(stderr, "Usage generator file_length alphabet_size\n");
        exit(EXIT_FAILURE);
    }
    int len = atoi(argv[1]);
    int alphabet_size = atoi(argv[2]);

    char alphabet[alphabet_size];

    for(int i = 0; i < alphabet_size; i += 1){
        alphabet[i] = (char) (i + 32);
    }
    for(int i = 0; i < len; i += 1){
        int index = rand() % alphabet_size;
        printf("%c", alphabet[index]);
    }
    return EXIT_SUCCESS;
#endif
#ifdef WORD_GEN
    if(argc != 4){
        fprintf(stderr, "Usage generator words_nb word_length alphabet_size words_length\n");
        exit(EXIT_FAILURE);
    }
    int word_nb = atoi(argv[1]);
    int word_len = atoi(argv[2]);
    int alphabet_size = atoi(argv[3]);

    char alphabet[alphabet_size];

    for(int i = 0; i < alphabet_size; i += 1){
        alphabet[i] = (char) (i + 33);
    }
    for(int i = 0; i < word_nb; i += 1){
        for(int j = 0; j < word_len; j += 1){
            int index = rand() % alphabet_size;
            printf("%c", alphabet[index]);
        }
        printf("\n");
    }
#endif
}