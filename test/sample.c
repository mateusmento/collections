#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <colldef.h>


#define node_new(type) node_new(sizeof(type))
#define list_new(type) list_new(sizeof(type))
#define list_select(this, type, fn) list_select(this, sizeof(type), cast(ListSelectFn, fn))
#define list_filter(this, fn) list_filter(this, cast(ListFilterFn, fn))


#define getdata(x) cast(void*, cast(Node*, x) + 1)
#define touser(x) cast(User*, getdata(x))
#define tocredentials(x) cast(UserCredentials*, getdata(x))

typedef struct {
	const char* username;
	const char* password;	
} UserCredentials;

typedef struct {
	size_t id;
	UserCredentials credentials;
	const char* email;
} User;

void fill_list(List* list, int length, const char* arr[])
{
	for (int i = 0; i < length; i+=2)
	{
		Node* node = node_new(User);
		User* user = touser(node);
		user->id = i/2;
		user->credentials.username = arr[i + 1];
		user->credentials.password = arr[i + 2];
		list_push(list, node);
	}
}

void print_list(List* list)
{
	for(Node* node = list->begin; node != NULL; node = node->next)
	{
		UserCredentials* user = tocredentials(node);
		printf("%s %s\n", user->username, user->password);
	}
}

void select_fn(User* srcData, UserCredentials* destData)
{
	*destData = srcData->credentials;
}

bool filter_fn(User* user)
{
	return user->id % 2 == 1;
}

int main(int argc, const char** argv)
{
	size_t length = argc % 2 != 1 ? argc : argc - 1;
	const char** arr = argv;

	List* user_list = list_new(User);

	fill_list(user_list, length, arr);
	
	List* user_list2 = list_filter(user_list, filter_fn);
	List* id_list = list_select(user_list2, sizeof(UserCredentials), (ListSelectFn)select_fn);
	
	print_list(id_list);

	return 0;
}
