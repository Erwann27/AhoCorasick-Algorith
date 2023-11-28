#ifndef __LIST_H__
#define __LIST_H__

typedef struct _list List;

// Create an empty list
extern List *create_list(void);

extern int is_empty(List *list);

extern size_t list_size(List *list);

// Append xptr to list
extern void append(List *list, const void *xptr);

// Retrieve last element from list
extern const void *retrieve(List *q);

// Dispose List list
extern void dispose_list(List **lptr);

#endif