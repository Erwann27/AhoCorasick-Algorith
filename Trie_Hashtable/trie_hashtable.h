#ifndef _HASH_TRIE_H_
#define _HASH_TRIE_H_

#define FILL_RATE 0.75

struct _list {
    int startNode, /* etat de depart de la transition */
    targetNode; /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next; /* maillon suivant */
};
typedef struct _list *TransitionList;

struct _trie {
    int insertedNode; /* Indice du noeud inséré */
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    TransitionList *transition; /* listes d’adjacence */
    char *finite; /* etats terminaux */
};
typedef struct _trie *Trie;

extern Trie createTrie(int maxNode);

extern int isInTrie(Trie trie, unsigned char *w);

extern int is_transition(Trie trie, int start_node, unsigned char letter);

extern int get_target(Trie trie, int start_node, unsigned char letter);

extern int is_finite_node(Trie trie, int node);

extern void insertInTrie(Trie trie, unsigned char *w);

extern void declare_finite_state(Trie trie, int node);

extern void create_transition(Trie trie, int start_node, char letter, int target_node);

extern void dispose_trie(Trie t);
#endif