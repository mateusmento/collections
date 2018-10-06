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

Node* list_push(List* this, Node* node)
{
	if (this == NULL) return NULL;

	// there is nothing to push if node is the end or NULL. if node is the
	// end then continuing the function would get a undesirable behaviour
	if (node == NULL) return NULL;
	if (node == this->end) return node;

	// link adjacents nodes of node if it comes from a chain of nodes.
	node_linkadjacents(node);

	// make node the end of the list
	node_attach(node, this->end, NULL);

	// the end go on level down if there is one
	if (this->end != NULL)
	{	
		this->end->next = node; 
	}

	// node always becomes the end
	this->end = node;

	// node should become the beginning if there is no one
	if (this->begin == NULL)
	{	
		this->begin = node;
	}

	this->count++; // count one more node

	return node;
}

List* list_select(List* list, size_t newuserdatasize, ListSelectFn fn)
{
	// new list for the selected data
	List* new_list = list_new(newuserdatasize);

	for (Node* node = list->begin; node != NULL; node = node->next)
	{
		// buffer for the selected data
		Node* new_node = node_new(newuserdatasize);
		list_push(new_list, new_node);

		// buildng of the selection is done by the user's callback
		fn(node + 1, new_node + 1); 
	}

	return new_list;
}

List* list_filter(List* this, ListFilterFn fn)
{
	// new list for the desired data
	List* new_list = list_new(this->userdatasize);

	for (Node* node = this->begin; node != NULL; node = node->next)
	{
		// if the criteria provired by the user is true 
		if (fn(node + 1))
		{
			// then the current node should be included as a copy
			Node* new_node = node_new(this->userdatasize);
			memcpy(new_node + 1, node + 1, this->userdatasize);
			list_push(new_list, new_node);
		}
	}

	return new_list;
}
