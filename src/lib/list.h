#ifndef LIST_H
#define LIST_H

typedef struct list List;

List * List_create();

void List_destroy(List *list);

int List_getSize(const List *list);

int List_insertItem(List *list, void *data, const int position);

void * List_removeItem(List *list, const int position);

void * List_getItem(List *list, const int position);

#endif