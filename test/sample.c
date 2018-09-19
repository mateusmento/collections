#include <collections.h>
#include <stdio.h>

typedef struct
{
	const char* username;
	const char* password;
} UserCredential;

typedef struct
{
	size_t id;
	UserCredential credential;
} User;


void create_users(List* list, char** arr, size_t length)
{
	for (int i = 0; i < length; i += 2)
	{
		Node* node = node_new(User);
		list_push(list, node);
		
		User* user = node_getuserdata(node);
		user->credential.username = arr[i];
		user->credential.password = arr[i + 1];
		user->id = i/2 + 1;
	}
}

void print_credentials(List* list)
{
	for (Node* node = list->begin; node != NULL; node = node->next)
	{
		UserCredential* credential = node_getuserdata(node);
		const char* username = credential->username;
		const char* password = credential->password;
		
		printf("%s %s\n", username, password);
	}
}

bool filter_fn(User* user)
{
	return user->id % 2 == 1;
}

void select_fn(User* user, UserCredential* credential)
{
	*credential = user->credential;
}

int main(int argc, char** argv)
{
	char** arr = argv + 1;
	size_t length = argc - 1;

	List* users = list_new(User);
	create_users(users, arr, length);
	List* users_odd = list_filter(users, filter_fn);
	List* credentials = list_select(users_odd, UserCredential, select_fn);
	print_credentials(credentials);

	return 0;
}
