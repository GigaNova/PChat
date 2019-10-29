// PChat.cpp : Defines the entry point for the application.
//

#include "PChat.h"
#include "PChatClient.h"
#include "../InputReader.h"

constexpr int SERVER_PORT = 2391;

int main()
{
	std::cout << "Please give the hostname: " << std::endl;
	const std::string host = InputReader::getInput();
	
	PChatClient client(host, SERVER_PORT);
	client.execute();
	
	return EXIT_SUCCESS;
}
