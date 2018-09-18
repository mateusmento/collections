#define LIST_C
#include <list.h>
#include <colldef.h>
#include <stdlib.h>
#include <string.h>

List* list_init(List* this, size_t userdatasize)
{
	this->begin = NULL;
	this->end = NULL;
	this->count = 0;
	this->userdatasize = userdatasize;
	return this;
}

List* list_new(size_t userdatasize)
{
	List* this = (List*)malloc(sizeof(List));
	return list_init(this, userdatasize);
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
	if (this == NULL) return NULL;

	// there is nothing to push if node is the end or NULL. if node is the
	// end then continuing the function would get a undesirable behaviour
	if (node == NULL) return NULL;
	if (node == this->end) return node;

	// link contiguos nodes of node if it comes from a chain of nodes.
	node_link(node->prev, node->next);

	// link node to the end
	node_linkto(node, this->end, NULL);

	// if list is not empty
	if (this->end != NULL)
	{	
		this->end->next = node; // the end go on level down
	}

	//  node always becomes the end
	this->end = node;

	// if list is empty 
	if (this->begin == NULL)
	{	
		this->begin = node; // node becomes the beginning
	}

	this->count++; // count one more node

	return node;
}

List* list_select(List* list, size_t newuserdatasize, ListSelectFn fn)
{
	List* new_list = list_new(newuserdatasize);

	for (Node* node = list->begin; node != NULL; node = node->next)
	{
		Node* new_node = node_new(newuserdatasize);
		list_push(new_list, new_node);
		fn(node + 1, new_node + 1);
	}

	return new_list;
}

List* list_filter(List* this, ListFilterFn fn)
{
	List* new_list = list_new(this->userdatasize);

	for (Node* node = this->begin; node != NULL; node = node->next)
	{
		if (fn(node + 1))
		{
			Node* new_node = node_new(this->userdatasize);
			memcpy(new_node + 1, node + 1, this->userdatasize);
			list_push(new_list, new_node);
		}
	}

	return new_list;
}

