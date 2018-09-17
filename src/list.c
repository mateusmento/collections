#include <list.h>


Node* node_init(Node* this)
{
	this->next = NULL;
	this->prev = NULL;
	return this;
}

List* list_init(List* this)
{
	this->begin = NULL;
	this->end = NULL;
	this->count = 0;
	return this;
}

Node* list_begin(List* this)
{
	return this->begin;
}

Node* list_end(List* this)
{
	return this->end;
}

Node* list_push(List* this, Node* node)
{
	// there is nothing to push if node is the end or NULL. 
	// if node is the end then continuing the function would get a undesirable behaviour
	if (node == NULL) return NULL;
	if (node == this->end) return node;

	// link the previous node to the next one if node has successor.
	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	
	// link the next node to the previous one if node has predecessor.
	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}

	// preparing node
	node->prev = this->end;	
	node->next = NULL;

	// if list is not empty
	if (this->end != NULL)
	{
		// the end go on level down
		this->end->next = node;
	}

	// if list is empty 
	if (this->begin == NULL)
	{
		// node becomes the beginning
		this->begin = node;
	}

	//  node always becomes the end
	this->end = node;

	// count one more node
	this->count++;

	return node;
}

