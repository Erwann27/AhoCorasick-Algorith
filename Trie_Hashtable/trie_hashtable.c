#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "trie_hashtable.h"

#define DEF_VALUE NULL

int hashFun(int node, unsigned char transition, Trie t);

Trie createTrie(int maxNode){
    Trie t = malloc(sizeof(struct _trie));
    if(t == NULL){
        fprintf(stderr, "Erreur malloc");
        exit(EXIT_FAILURE);
    }
    t->insertedNode = 0;
    t->maxNode = maxNode;
    t->nextNode = 1;
    TransitionList *hashtable = malloc((size_t)((maxNode) * (1 / FILL_RATE)) * sizeof(struct _list));
    if(hashtable == NULL){
        fprintf(stderr, "Erreur allocation transition\n");
        return NULL;
    }
    t->finite = calloc((size_t)maxNode, sizeof(char));
    if(t->finite == NULL){
        free(hashtable);
        fprintf(stderr, "Erreur allocation finite\n");
        return NULL;
    }
    for(int i = 0; i < maxNode * (1 / FILL_RATE); i += 1){
        hashtable[i] = DEF_VALUE;
    }
    t->transition = hashtable;
    return t;
}

int isInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return -1;
    }
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        int hashPosition = hashFun(currentNode, w[i], trie);
        if(trie->transition[hashPosition] == NULL){
            return 0;
        }
        TransitionList list = trie->transition[hashPosition];
        while (list->next != NULL && list->letter != w[i] 
                && list->startNode != currentNode){
            list = list->next;
        }
        if(list->letter != w[i] && list->startNode != currentNode){
            return 0;
        }
        currentNode = list->targetNode;
    }
    if(trie->finite[currentNode]){
        return 1;
    }
    return 0;
}

int is_transition(Trie trie, int start_node, unsigned char letter){
    int hashPosition = hashFun(start_node, letter, trie);
    if(trie->transition[hashPosition] == NULL){
        return 0;
    }
    TransitionList list = trie->transition[hashPosition];
    while (list->next != NULL && (list->startNode != start_node || list->letter != letter)){
            list = list->next;
    }
    if(list->startNode != start_node || list->letter != letter){
        return 0;
    }
    return 1;
}

int get_target(Trie trie, int start_node, unsigned char letter){
    int hashPosition = hashFun(start_node, letter, trie);
    if(trie->transition[hashPosition] == NULL){
        return -1;
    }
    TransitionList list = trie->transition[hashPosition];
    while (list->next != NULL && (list->startNode != start_node || list->letter != letter)){
        list = list->next;
    }

    if(list->startNode != start_node || list->letter != letter){
        return -1;
    }
    return list->targetNode;
}

void insertInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return;
    }
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        int hashPosition = hashFun(currentNode, w[i], trie);
        // LA FONCTION DE HACHAGE NOUS RENVOIE UNE POSITION OU AUCUNE
        // LISTE N'EST INITIALISEE
        if(trie->transition[hashPosition] == NULL){
            TransitionList list = malloc(sizeof(struct _list));
            if(list == NULL){
                fprintf(stderr, "Erreur allocation list\n");
                return;
            }
            list->startNode = currentNode;
            list->letter = w[i];
            list->targetNode = trie->nextNode;
            list->next = NULL;
            trie->transition[hashPosition] = list;
            currentNode = trie->nextNode;
            trie->nextNode += 1;
        }
        else {
            TransitionList list = trie->transition[hashPosition];
            while (list->next != NULL && list->letter != w[i] 
                && list->startNode != currentNode){
                list = list->next;                
            }
            // LA LISTE OBTENUE AVEC LA FONCTION DE HACHAGE NE CONTIENT
            // PAS LE NOEUD SOUHAITE
            if(list->next == NULL && list->startNode != currentNode){
                TransitionList nextListe = malloc(sizeof(struct _list));
                if(nextListe == NULL){
                    fprintf(stderr, "Erreur allocation list\n");
                    return;
                }
                list->next = nextListe;
                nextListe->startNode = currentNode;
                nextListe->letter = w[i];
                nextListe->targetNode = trie->nextNode;
                currentNode = trie->nextNode;
                trie->nextNode += 1;
            }

            // LA LISTE OBTENUE CONTIENT LE NOEUD SOUHAITE
            else {
                currentNode = list->targetNode;
            }
        }
    }
    trie->insertedNode = currentNode;
    trie->finite[currentNode] = 1;
}

void create_transition(Trie trie, int start_node, char letter, int target_node){
    int hashPosition = hashFun(start_node, (unsigned char)letter, trie);
    if(trie->transition[hashPosition] == NULL){
        TransitionList list = malloc(sizeof(struct _list));
        if(list == NULL){
            fprintf(stderr, "Erreur allocation list\n");
            return;
        }
        list->startNode = start_node;
        list->letter = (unsigned char)letter;
        list->targetNode = target_node;
        list->next = NULL;
        trie->transition[hashPosition] = list;
        trie->nextNode += 1;
    } else {
        TransitionList list = trie->transition[hashPosition];
        while (list->next != NULL){
            list = list->next;                
        }
        // LA LISTE OBTENUE AVEC LA FONCTION DE HACHAGE NE CONTIENT
        // PAS LE NOEUD OUF
            TransitionList nextListe = malloc(sizeof(struct _list));
            if(nextListe == NULL){
                fprintf(stderr, "Erreur allocation list\n");
                return;
            }
            list->next = nextListe;
            nextListe->startNode = start_node;
            nextListe->letter = (unsigned char)letter;
            nextListe->targetNode = target_node;
            nextListe->next = NULL;
        }
}

void dispose_trie(Trie t) {
    TransitionList *lists = t -> transition;

    for(int i = 0; i < t->maxNode * (1 / FILL_RATE); ++i) {
        TransitionList list = lists[i];
        while(list != NULL) {
            TransitionList tmp = list -> next;
            free(list);
            list = tmp;
        }
    }
    free(t->transition);
    free(t->finite);
    free(t);

}

int hashFun(int node, unsigned char transition, Trie t){
    return(node * 17 + transition * 13) % (int)(t->maxNode * FILL_RATE);
}

