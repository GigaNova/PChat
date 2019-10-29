#pragma once
#include <boost/asio.hpp>
#include "User.h"

class PChatServer
{
public:
	PChatServer(int _port);

	void execute();
	void broadCast(const std::string& _message, User* _exclusion) const;
	void setUsername(const std::string& _username, User* _user);
	void removeUser(User* _user);

	const std::vector<std::shared_ptr<User>>& getUsers() const;
private:
	int m_port;

	std::vector<std::shared_ptr<User>> m_users;
	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};
