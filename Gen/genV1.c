#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "expected arguments : a text length and alphabet size\n");
    exit(EXIT_FAILURE);
  }
  int len = atoi(argv[1]);
  int alph_size = atoi(argv[2]);
  char alph[alph_size];
  for (int i = 0; i < alph_size; ++i) {
    alph[i] = (char) (i + 33);
  }
  for (int i = 0; i < len; ++i) {
    int index = rand() % alph_size;
    printf("%c", alph[index]);
  }
  return EXIT_SUCCESS;
}
