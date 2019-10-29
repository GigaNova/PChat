#pragma once
#include <boost/asio/ip/tcp.hpp>
#include "PChatClient.h"
#include "../Thread.h"

class WriteThread : public Thread
{
public:
	WriteThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatClient* _instance);
	
private:
	void run() const override;

	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
	PChatClient* m_instance;
};
