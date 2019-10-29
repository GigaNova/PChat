#pragma once
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <condition_variable>

struct ProgramStatus
{
	std::mutex mutex;
	std::condition_variable condition;
	bool finished = false;
};

class PChatClient
{
public:
	static ProgramStatus m_status;
	
	PChatClient(const std::string& _host, int _port);

	void execute();
	
	const std::string& getUserName() const;
	void setUserName(const std::string& _username);
private:
	std::string m_username;
	
	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
	std::string m_host;
	int m_port;
};
