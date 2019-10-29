#include "ReadThread.h"
#include <boost/bind/bind.hpp>
#include "../InputReader.h"
#include "PChatClient.h"
#include <thread>

ReadThread::ReadThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatClient* _instance) : m_socket(_socket), m_instance(_instance)
{
}

void ReadThread::run() const
{
	while (!PChatClient::m_status.finished) {
		auto response = InputReader::getInput(m_socket.get());
		std::cout << response << std::endl;
	}
}
