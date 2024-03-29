#ifndef _TRANSITION_TABLE_H_
#define _TRANSITION_TABLE_H_

struct _trie
{
    int insertedNode; /* Indice du noeud inséré */
    int maxNode;      /* Nombre maximal de noeuds du trie */
    int nextNode;     /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite;     /* etats terminaux */
};

typedef struct _trie *Trie;

extern Trie createTrie(int maxNode);

extern int is_transition(Trie trie, int start_node, unsigned char letter);

extern int isInTrie(Trie trie, unsigned char *w);

extern int get_target(Trie trie, int start_node, unsigned char letter);

extern void insertInTrie(Trie trie, unsigned char *w);

extern void print_trie(Trie t);

extern void dispose_trie(Trie t);

extern void create_transition(Trie trie, int start_node, char letter, int target_node);

#endif