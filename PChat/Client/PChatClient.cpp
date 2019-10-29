#include "PChatClient.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/connect.hpp>
#include <iostream>
#include "ReadThread.h"
#include "WriteThread.h"

ProgramStatus PChatClient::m_status{};

PChatClient::PChatClient(const std::string& _host, int _port) : m_host(_host), m_port(_port)
{
	
}

void PChatClient::execute()
{
	boost::asio::io_service service;
	const boost::asio::ip::tcp::resolver::query resolverQuery(m_host, std::to_string(m_port), boost::asio::ip::tcp::resolver::query::numeric_service);
	boost::asio::ip::tcp::resolver resolver(service);

	auto it = resolver.resolve(resolverQuery);
	
	m_socket = std::make_shared<boost::asio::ip::tcp::socket>(service);
	boost::asio::connect(*m_socket, it);

	try {
		auto rThread = new ReadThread(m_socket, this);
		auto wThread = new WriteThread(m_socket, this);

		rThread->start();
		wThread->start();
	}
	catch (std::exception& e)
	{
		std::cout << "Could not start client: " << e.what() << std::endl;
	}

	while(!m_status.finished)
	{
		//Wait
	}

	m_socket->close();
}

const std::string& PChatClient::getUserName() const
{
	return m_username;
}

void PChatClient::setUserName(const std::string& _username)
{
	m_username = _username;
}
