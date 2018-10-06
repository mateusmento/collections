#include <collections.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


void verify(int is_correct, const char* msg)
{
	if (!is_correct)
	{
		puts(msg);
		exit(0);
	}
}

void select_fn(int* n, int* s)
{
	*s = *n + 1;
}

bool filter_fn(int* n)
{
	return *n % 2 == 0;
}

int main()
{
	List l;
	List* list = &l;

	/// test for list_init ////////////////////
	size_t sizeof_int = sizeof(int);
	list_init(&l, sizeof_int);
	assert(list->begin == NULL);
	assert(list->end == NULL);
	assert(list->count == 0);
	assert(list->userdatasize == sizeof_int);

	/// test for list_new ////////////////////
	list = list_new(int);
	assert(list->begin == NULL);
	assert(list->end == NULL);
	assert(list->count == 0);
	assert(list->userdatasize == sizeof_int);

	/// test for list_push //////////////////
	Node* node1 = node_new(int);
	list_push(list, node1); // list -> node1
	assert(list->begin == list->end);
	assert(list->begin == node1);
	assert(list->count == 1);

	assert(node1->next == NULL);
	assert(node1->prev == NULL);


	Node* node2 = node_new(int);
	list_push(list, node2); // list -> node1 <--> node2
	assert(list->begin == node1);
	assert(list->end == node2);
	assert(list->count == 2);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == NULL);

	Node* node3 = node_new(int);
	list_push(list, node3); // list -> node1 <--> node2 <--> node3
	assert(list->begin == node1);
	assert(list->end == node3);
	assert(list->count == 3);

	assert(node1->prev == NULL);
	assert(node1->next == node2);
	assert(node2->prev == node1);
	assert(node2->next == node3);
	assert(node3->prev == node2);
	assert(node3->next == NULL);

	list_push(list, node2); // list -> node1 <--> node3 <--> node2
	assert(list->begin == node1);
	assert(list->end == node2);
	assert(list->count == 4);

	assert(node1->prev == NULL);
	assert(node1->next == node3);
	assert(node3->prev == node1);
	assert(node3->next == node2);
	assert(node2->prev == node3);
	assert(node2->next == NULL);

	//////////////////////////////////////////

	/// test for list_select /////////////////

	int count = 1;
	for (Node* node = list->begin; node != NULL; node = node->next)
	{
		int* n = node_getuserdata(node);
		*n = count++;
	}

	List* num_list = list_select(list, int, select_fn);
	Node* beg = num_list->begin;
	assert(*cast(int*, node_getuserdata(beg)) == 2);
	assert(*cast(int*, node_getuserdata(beg->next)) == 3);
	assert(*cast(int*, node_getuserdata(beg->next->next)) == 4);

	for (Node* node = num_list->begin; node != NULL; node = node->next)
	{
		int n = *cast(int*, node_getuserdata(node));
		printf("%i\n", n);
	}
	

	/// test for list_filter ////////////////
	
	List* filtered_list = list_filter(num_list, filter_fn);
	beg = filtered_list->begin;
	assert(*cast(int*, node_getuserdata(beg)) == 2);
	assert(*cast(int*, node_getuserdata(beg->next)) == 4);
	assert(beg->next->next == NULL);
}
