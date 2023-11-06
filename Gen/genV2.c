#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
 if (argc != 4) {
    fprintf(stderr, "expected arguments : a word number, a word length and alphabet size\n");
    exit(EXIT_FAILURE);
  }
  int word_nb = atoi(argv[1]);
  int len = atoi(argv[2]);
  int alph_size = atoi(argv[3]);

  char alph[alph_size];
  for (int i = 0; i < alph_size; ++i) {
    alph[i] = (char) (i + 33);
  }
  for (int j = 0; j < word_nb; ++j) {
    for (int i = 0; i < len; ++i) {
      int index = rand() % alph_size;
      printf("%c", alph[index]);
    }
    printf(" ");
  }
  return EXIT_SUCCESS;
}
