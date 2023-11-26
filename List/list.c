#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

typedef struct clist clist;

struct clist {
  const void *value;
  clist *next;
//   clist *prev;
};

struct _list {
  clist *head;
  clist *tail;
  size_t size;
};

typedef struct _list List;


List *create_list(void){
    List *l = malloc(sizeof(List));
    if(l == NULL){
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void append(List *list, const void *xptr){
    if(xptr == NULL){
        dispose_list(&list);
        exit(EXIT_FAILURE);
    }
    clist *elt = malloc(sizeof *elt);
    if(elt == NULL){
        dispose_list(&list);
        exit(EXIT_FAILURE);
    }
    elt->value = xptr;
    elt->next = NULL;
    if(list->size == 0){
        list->head = elt;
    } else {
        clist *prev = list->tail;
        prev->next = elt;
    }
    list->tail = elt;
    list->size += 1;
}

const void *retrieve(List *list){
    if(list->size == 0){
        dispose_list(&list);
        exit(EXIT_FAILURE);
    }
    clist *elt = list->head;
    list->head = elt->next;
    const void *xptr = elt->value;
    free(elt);
    list->size -= 1;
    return xptr;
}

void dispose_list(List **lptr){
    if(*lptr == NULL){
        exit(EXIT_FAILURE);
    }
    clist *elt = (*lptr)->head;
    while (elt != NULL){
        clist *t = elt;
        elt = elt->next;
        free(t);
    }
    free(*lptr);
    *lptr = NULL;
}