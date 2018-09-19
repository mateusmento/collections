#include <collections.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main()
{
	/// test for node_new //////////////////////////
	Node* node = node_new(int);
	assert(node->next == NULL);
	assert(node->prev == NULL);

	///	test for node_init /////////////////////////
	Node node_value;
	node_init(&node_value);
	assert(node->next == NULL);
	assert(node->prev == NULL);

	/// test for node_linkto ///////////////////////
	Node* node1 = node_new(int);
	Node* node2 = node_new(int);
	node_linkto(node1, node2);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == NULL);

	/// test for node_attach ///////////////////////
	Node* node3 = node_new(int);
	node_attach(node3, node1, node2);

	assert(node3->next == node2);
	assert(node3->prev == node1);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == NULL);

	/// test for node_linkbetween /////////////////
	Node* node4 = node_new(int);
	node_linkbetween(node4, node1, node2);
	
	assert(node4->next == node2);
	assert(node4->prev == node1);
	
	assert(node1->prev == NULL);
	assert(node1->next == node4);
	assert(node2->prev == node4);
	assert(node2->next == NULL);

	/// test for node_linkadjacents //////////////
	node_linkadjacents(node4);

	assert(node4->next == node2);
	assert(node4->prev == node1);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == NULL);

	/// test for node_extract ///////////////////
	Node* node5 = node_new(int);
	node_linkbetween(node5, node1, node2);
	node_extract(node5);

	assert(node5->next == NULL);
	assert(node5->prev == NULL);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == NULL);
}
