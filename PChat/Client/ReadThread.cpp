#include "ReadThread.h"
#include <boost/bind/bind.hpp>
#include <boost/thread/thread_only.hpp>
#include "../InputReader.h"
#include "PChatClient.h"

ReadThread::ReadThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatClient* _instance) : m_socket(_socket), m_instance(_instance)
{
	boost::thread thread(boost::bind(&ReadThread::run, this));
	thread.detach();
}

void ReadThread::run() const
{
	while (true) {
		auto response = InputReader::getInput(m_socket.get());
		std::cout << response << std::endl;
	}
}
