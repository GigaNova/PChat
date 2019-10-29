#include "PChatServer.h"
#include <iostream>

PChatServer::PChatServer(int _port) : m_port(_port)
{
}

void PChatServer::execute()
{
	boost::asio::io_service service;
	boost::asio::ip::tcp::acceptor acceptor(
		service,
		boost::asio::ip::tcp::endpoint(
			boost::asio::ip::tcp::v4(), 
			m_port
		)
	);

	std::cout << "Starting server on port: " << m_port << std::endl;
	
	m_socket = std::make_shared<boost::asio::ip::tcp::socket>(service);
	
	while(true)
	{
		std::cout << "Waiting..." << std::endl;
		
		auto socket = std::make_shared<boost::asio::ip::tcp::socket>(service);
		acceptor.accept(*socket);

		std::cout << "User Connected." << std::endl;
		
		auto newUser = std::make_shared<User>(new UserThread(socket, this), "Unnamed");
		m_users.push_back(newUser);
		newUser->startThread();
	}
}

void PChatServer::broadCast(const std::string& _message, User* _exclusion) const
{
	for(auto&& user : m_users)
	{
		if(user.get() != _exclusion)
		{
			user->sendMessage(_message);
		}
	}
}

void PChatServer::setUsername(const std::string& _username, User* _user)
{
	const auto user = std::find_if(m_users.begin(), m_users.end(),
		[&](auto const& o) { return o.get() == _user; });

	if(user != m_users.end())
	{
		(*user)->setName(_username);
	}
}

void PChatServer::removeUser(User* _user)
{
	m_users.erase(
		std::remove_if(m_users.begin(), m_users.end(),
			[&](auto const& o) { return o.get() == _user; }
		),
		m_users.end()
	);
}

const std::vector<std::shared_ptr<User>>& PChatServer::getUsers() const
{
	return m_users;
}
