#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include "colldef.h"


typedef struct Node Node;

struct Node
{
	Node* next;
	Node* prev;
};


Node* node_init(Node* this);
Node* node_new(size_t userdatasize);
void node_free(Node* this);

void node_linkto(Node* this, Node* target);
void node_linkadjacents(Node* this);
void node_linkbetween(Node* this, Node* prev, Node* next);
void node_attach(Node* this, Node* prev, Node* next);
void node_extract(Node* this);

#define node_getuserdata(this) cast(void*, cast(Node*, this + 1))

#endif
