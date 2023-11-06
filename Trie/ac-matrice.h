#ifndef _TRANSITION_TABLE_H_
#define _TRANSITION_TABLE_H_

struct _trie
{
    int maxNode;      /* Nombre maximal de noeuds du trie */
    int nextNode;     /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite;     /* etats terminaux */
};

typedef struct _trie *Trie;

extern Trie createTrie(int maxNode);

extern void insertInTrie(Trie trie, unsigned char *w);

extern int isInTrie(Trie trie, unsigned char *w);

extern void print_trie(Trie t);

extern void dispose_trie(Trie t);
#endif