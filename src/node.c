#include <node.h>
#include <colldef.h>
#include <stdlib.h>

Node* node_init(Node* this)
{
	this->next = NULL;
	this->prev = NULL;
	return this;
}

Node* node_new(size_t userdatasize)
{
	Node* node = (Node*) malloc(sizeof(Node) + userdatasize);
	return node_init(node);
}

void node_linkto(Node* first_node, Node* second_node)
{
	// if first_node is not null, its next node is second_node
	if(first_node != NULL)
	{
		first_node->next = second_node;
	}

	// if second_node is not null, its previous node is first_node
	if (second_node != NULL)
	{
		second_node->prev = first_node;
	}
}

void node_linkadjacents(Node* this)
{
	if (this == NULL) return;
	node_linkto(this->prev, this->next);
}

void node_linkbetween(Node* this, Node* prev, Node* next)
{
	if (this == NULL)
	{
		prev->next = NULL;
		next->prev = NULL;
	}
	else
	{
		node_linkto(prev, this);
		node_linkto(this, next);
	}
}

void node_attach(Node* this, Node* prev, Node* next)
{
	if (this == NULL) return;
	this->next = next;
	this->prev = prev;
}

void node_extract(Node* this)
{
	node_linkadjacents(this);
	node_attach(this, NULL, NULL);
}

void node_free(Node* this)
{
	free(this);
}

