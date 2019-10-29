#include "UserThread.h"
#include <boost/thread.hpp>
#include <boost/asio/write.hpp>
#include "PChatServer.h"
#include <iostream>
#include "../InputReader.h"

UserThread::UserThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatServer* _instance) : m_socket(_socket), m_instance(_instance)
{
	
}

void UserThread::start()
{
	boost::thread thread(boost::bind(&UserThread::run, this));
	thread.detach();
}

void UserThread::setOwner(User* _owner)
{
	m_owner = _owner;
}

void UserThread::run() const
{
	const auto username = InputReader::getInput(m_socket.get());

	m_instance->setUsername(username, m_owner);

	std::string message;
	while(message != "quit" && message != "later")
	{
		message = InputReader::getInput(m_socket.get());
		const auto finalMessage = "[[" + username + "]]: " + message;
		m_instance->broadCast(finalMessage, m_owner);
	}

	m_instance->removeUser(m_owner);
	m_socket->close();

	m_instance->broadCast(std::string(username + " left."), m_owner);

	boost::this_thread::interruption_point();
}

void UserThread::sendMessage(const std::string& _message) const
{
	InputReader::write(_message, m_socket.get());
}