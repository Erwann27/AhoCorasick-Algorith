#ifndef __AHO_CORASICK__
#define __AHO_CORASICK__
#include <stdlib.h>

// aho_corasick : Renvoie le nombre d'occurrences des word_count mots contenus dans trie
//  dans text de longueur text_length.
size_t aho_corasick(char **word_list, size_t word_count, unsigned char *text, size_t text_length);

#endif