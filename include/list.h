#ifndef LIST_H
#define LIST_H

#ifndef NULL
#define NULL ((void*) 0)
#endif


typedef struct Node Node;
typedef struct List List;

struct Node
{
	Node* prev;
	Node* next;
};

struct List
{
	Node* begin;
	Node* end;
	unsigned long count;
};

Node* node_init(Node* this);

List* list_init(List* this);
Node* list_begin(List* this);
Node* list_end(List* this);

Node* list_push(List* this, Node* node);


#define cast(type, value) ((type) (value))
#define node_newarr(type, size) cast(Node*, calloc(sizeof(Node) + sizeof(type), size))
#define node_new(type) node_newarr(type, 1)
#define list_new() cast(List*, calloc(sizeof(List), 1))


#endif
