#include "WriteThread.h"
#include "../InputReader.h"
#include <boost/asio/write.hpp>
#include <boost/thread/thread_only.hpp>

WriteThread::WriteThread(std::shared_ptr<boost::asio::ip::tcp::socket> _socket, PChatClient* _instance) : m_socket(_socket), m_instance(_instance)
{
	boost::thread thread(boost::bind(&WriteThread::run, this));
	thread.detach();
}

void WriteThread::run() const
{
	std::cout << "State your username: " << std::endl;
	const std::string userName = InputReader::getInput();
	m_instance->setUserName(userName);
	InputReader::write(userName, m_socket.get());

	std::cout << "Welcome, " << userName << std::endl;
	
	std::string message;
	while (message != "quit" && message != "later")
	{
		message = InputReader::getInput();
		InputReader::write(message, m_socket.get());
	};

	m_socket->close();

	boost::this_thread::interruption_point();
}
