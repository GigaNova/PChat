// PChat.cpp : Defines the entry point for the application.
//

#include "PChat.h"
#include "PChatServer.h"

constexpr int SERVER_PORT = 2391;

int main()
{
	PChatServer server(SERVER_PORT);
	server.execute();
	
	return EXIT_SUCCESS;
}
