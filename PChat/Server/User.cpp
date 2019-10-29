#include "User.h"

User::User(UserThread* _thread, const std::string& _username) : m_thread(std::unique_ptr<UserThread>(_thread)), m_username(_username)
{
	m_thread->setOwner(this);
}

void User::startThread() const
{
	m_thread->start();
}

void User::sendMessage(const std::string& _message) const
{
	m_thread->sendMessage(_message);
}

const std::string& User::getName() const
{
	return m_username;
}

void User::setName(const std::string& _username)
{
	m_username = _username;
}

UserThread* User::getThread() const
{
	return m_thread.get();
}
