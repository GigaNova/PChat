#pragma once
#include <string>
#include <memory>
#include "UserThread.h"

class User
{
public:
	User(UserThread* _thread, const std::string& _username);

	void startThread() const;
	void sendMessage(const std::string& _message) const;
	
	const std::string& getName() const;
	void setName(const std::string& _username);
	
	UserThread* getThread() const;
private:
	std::unique_ptr<UserThread> m_thread;
	std::string m_username;
};
