#ifndef _HASH_TRIE_H_
#define _HASH_TRIE_H_

#define FILL_RATE 0.75

struct _list {
int startNode, /* etat de depart de la transition */
targetNode; /* cible de la transition */
unsigned char letter; /* etiquette de la transition */
struct _list *next; /* maillon suivant */
};
typedef struct _list *List;

struct _trie {
int maxNode; /* Nombre maximal de noeuds du trie */
int nextNode; /* Indice du prochain noeud disponible */
List *transition; /* listes d’adjacence */
char *finite; /* etats terminaux */
};
typedef struct _trie *Trie;

extern Trie createTrie(int maxNode);

extern void insertInTrie(Trie trie, unsigned char *w);

extern int isInTrie(Trie trie, unsigned char *w);

#endif