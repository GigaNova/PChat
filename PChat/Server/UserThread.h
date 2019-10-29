#pragma once
#include <boost/asio/ip/tcp.hpp>
#include "../Thread.h"

class PChatServer;
class User;

class UserThread : public Thread
{
public:
	UserThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatServer* _instance);

	void start();
	void setOwner(User* _owner);
	
	void sendMessage(const std::string& _message) const;
private:
	void run() const;
	
	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
	PChatServer* m_instance;
	User* m_owner;
};
