#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define touser(x) cast(User*, cast(Node*, x) + 1);

typedef struct {
	size_t id;
	const char* username;
	const char* password;
	const char* email;
} User;

void fill_list(List* list, int length, const char* arr[])
{
	for (int i = 0; i < length; i+=2)
	{
		Node* node = node_new(User);
		User* user = touser(node);
		user->id = i/2;
		user->username = arr[i + 1];
		user->password = arr[i + 2];
		list_push(list, node);
	}
}

void print_list(List* list)
{
	for(Node* node = list->begin; node != NULL; node = node->next)
	{
		User* user = touser(node);
		printf("%s %s\n", user->username, user->password);
	}
}

int main(int argc, const char** argv)
{
	size_t length = argc % 2 != 1 ? argc : argc - 1;
	const char** arr = argv;

	List* list = list_new();
	list_init(list);

	fill_list(list, length, arr);
	print_list(list);

	return 0;
}

