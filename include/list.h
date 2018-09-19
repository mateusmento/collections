#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

#include "node.h"



typedef struct List List;

struct List
{
	Node* begin;
	Node* end;
	size_t count;
	size_t userdatasize;
};


List* list_init(List* this, size_t userdatasize);
List* list_new(size_t userdatasize);

Node* list_push(List* this, Node* node);

typedef void (*ListSelectFn)(void*, void*);
typedef bool (*ListFilterFn)(void*);

List* list_select(List* this, size_t sizeToAllocate, ListSelectFn fn);
List* list_filter(List* this, ListFilterFn fn);

#endif
