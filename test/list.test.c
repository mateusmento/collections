#include <stdio.h>
#include <list.h>
#include <stdlib.h>


void assert(int is_correct, const char* msg, const char* code)
{
	if (!is_correct)
	{
		printf("%s\nExpression is not true: %s\n", msg, code);
		exit(1);
	}
}

#define assert(x, m) assert(x, m, #x)

void test_list_init(List* list, const char* msg)
{
	assert(list->begin == NULL, msg);
	assert(list->end == NULL, msg);
	assert(list->count == 0, msg);
}

void test_list_accessors(List* list, Node* begin, Node* end, const char* msg)
{
	assert(list_begin(list) == begin, msg);
	assert(list_end(list) == end, msg);
}

void test_node(Node* node, Node* prev, Node* next, const char* msg)
{
	assert(node->prev == prev, msg);
	assert(node->next == next, msg);
}

int main()
{
	Node node, another_node, third_node;
	List list;


	// testing node initializer
	node_init(&node);
	node_init(&another_node);
	node_init(&third_node);
	test_node(&node, NULL, NULL, "Error on testing node");
	
	
	// testing list accessors
	list.begin = &node;
	list.end = &another_node;
	test_list_accessors(&list, &node, &another_node, "Error on testing list accessors");


	// testing list initializer
	list_init(&list);
	test_list_init(&list, "Error on testing list intializer");	


	// tesing the first insertion
	list_push(&list, &node);
	test_list_accessors(&list, &node, &node, "Error on testing list accessors on the first insertion");
	test_node(&node, NULL, NULL, "Error on testing node on the first insertion");


	// testing the second insertion
	list_push(&list, &another_node);
	test_list_accessors(&list, &node, &another_node, "Error on testing list accessors on the second insertion");
	test_node(&node, NULL, &another_node, "Error on testing node on the second insertion");
	test_node(&another_node, &node, NULL, "Error on testing another_node on the second insertion");


	// testing the third insertion
	list_push(&list, &third_node);
	test_list_accessors(&list, &node, &third_node, "Error on testing list accessors on the third insertion");
	test_node(&node, NULL, &another_node, "Error on testing node on the third insertion");
	test_node(&another_node, &node, &third_node, "Error on testing another_node on the third insertion");
	test_node(&third_node, &another_node, NULL, "Error on testing third_node on the third insertion");

	// testing the fourth insertion. push another_node to the end
	list_push(&list, &another_node);
	test_list_accessors(&list, &node, &another_node, "Error on testing list accessors on the fourth insertion");
	test_node(&node, NULL, &third_node, "Error on testing node on the fourth insertion");
	test_node(&third_node, &node, &another_node, "Error on testing third_node on the fourth insertion");
	test_node(&another_node, &third_node, NULL, "Error on testing another_node on the fourth insertion");
}

