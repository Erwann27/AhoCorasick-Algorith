#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
 if (argc != 5) {
    fprintf(stderr, "expected arguments : a word number, a minimal word length,"\
      " a maximal word length, and alphabet size\n");
    exit(EXIT_FAILURE);
  }
  int word_nb = atoi(argv[1]);
  int min_len = atoi(argv[2]);
  int max_len = atoi(argv[3]);
  int alph_size = atoi(argv[4]);

  char alph[alph_size];
  for (int i = 0; i < alph_size; ++i) {
    alph[i] = (char) (i + 33);
  }
  for (int j = 0; j < word_nb; ++j) {
    int len = (rand() % (max_len - min_len + 1)) + min_len;
    for (int i = 0; i < len; ++i) {
      int index = rand() % alph_size;
      printf("%c", alph[index]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
