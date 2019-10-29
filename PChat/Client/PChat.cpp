// PChat.cpp : Defines the entry point for the application.
//

#include "PChat.h"
#include "PChatClient.h"

constexpr int SERVER_PORT = 2391;

int main()
{
	PChatClient client("127.0.0.1", SERVER_PORT);
	client.execute();
	
	return EXIT_SUCCESS;
}
