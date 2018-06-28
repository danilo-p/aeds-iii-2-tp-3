#ifndef LIST_H
#define LIST_H

typedef struct list List;

List * List_create();

void List_destroy(List *list);

int List_getSize(List *list);

int List_insertItem(List *list, void *data, int position);

void * List_removeItem(List *list, int position);

void * List_getItem(List *list, int position);

#endif