#pragma once
#include <boost/asio/ip/tcp.hpp>
#include "../Thread.h"

class PChatClient;

class ReadThread : public Thread
{
public:
	ReadThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatClient* _instance);

private:
	void run() const override;

	std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
	PChatClient* m_instance;
};
