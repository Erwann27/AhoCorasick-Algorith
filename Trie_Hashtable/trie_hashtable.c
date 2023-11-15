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
    t->maxNode = maxNode;
    t->nextNode = 1;
    t->transition = malloc((size_t)(maxNode) * sizeof(List *));
    if(t->transition == NULL){
        fprintf(stderr, "Erreur allocation transition\n");
        return NULL;
    }
    t->finite = malloc((size_t)maxNode * sizeof(int));
    if(t->finite == NULL){
        free(t->transition);
        fprintf(stderr, "Erreur allocation finite\n");
        return NULL;
    }
    for(int i = 0; i < maxNode * (1 / FILL_RATE); i += 1){
        t->transition[i] = DEF_VALUE;
    }
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
        List list = trie->transition[hashPosition];
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

int is_transition(Trie trie, int start_node, char letter){
    int hashPosition = hashFun(start_node, (unsigned char)letter, trie);
    if(trie->transition[hashPosition] == NULL){
        return 0;
    }
    List list = trie->transition[hashPosition];
    while (list->next != NULL && list->letter != letter){
            list = list->next;
    }
    if(list->next == NULL){
        return 0;
    }
    return 1;
}

void insertInTrie(Trie trie, unsigned char *w){
    if(w == NULL){
        fprintf(stderr, "Erreur w == NULL\n");
        return;
    }
    int currentNode = 0;
    for(int i = 0; w[i] != '\0'; i += 1){
        // printf("Noeud courrant : %d\n", currentNode);
        int hashPosition = hashFun(currentNode, w[i], trie);
        // printf("Postion table hachage : %d\n", hashPosition);

        // LA FONCTION DE HACHAGE NOUS RENVOIE UNE POSITION OU AUCUNE
        // LISTE N'EST INITIALISEE
        if(trie->transition[hashPosition] == NULL){
            List list = malloc(sizeof(List));
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
            List list = trie->transition[hashPosition];
            while (list->next != NULL && list->letter != w[i] 
                && list->startNode != currentNode){
                list = list->next;                
            }
            // LA LISTE OBTENUE AVEC LA FONCTION DE HACHAGE NE CONTIENT
            // PAS LE NOEUD SOUHAITE
            if(list->next == NULL && list->startNode != currentNode){
                List nextListe = malloc(sizeof(List));
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
                // printf("J'ai trouve la lettre %c\n", list->letter);
                currentNode = list->targetNode;
            }
        }
    }
    trie->finite[currentNode] = 1;
}

void create_transition(Trie trie, int start_node, char letter, int target_node){
    int hashPosition = hashFun(start_node, (unsigned char)letter, trie);
    if(trie->transition[hashPosition] == NULL){
        List list = malloc(sizeof(List));
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
        List list = trie->transition[hashPosition];
        while (list->next != NULL && list->letter != letter 
            && list->startNode != start_node){
            list = list->next;                
        }
        // LA LISTE OBTENUE AVEC LA FONCTION DE HACHAGE NE CONTIENT
        // PAS LE NOEUD OUF
        if(list->next == NULL && list->startNode != start_node){
            List nextListe = malloc(sizeof(List));
            if(nextListe == NULL){
                fprintf(stderr, "Erreur allocation list\n");
                return;
            }
            list->next = nextListe;
            nextListe->startNode = start_node;
            nextListe->letter = (unsigned char)letter;
            nextListe->targetNode = target_node;
        }
    }
}



int hashFun(int node, unsigned char transition, Trie t){
    return(node * 17 + transition * 13) % (int)(t->maxNode * FILL_RATE);
}
