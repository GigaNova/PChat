#pragma once
#include <string>
#include <iostream>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>

class InputReader
{
public:
	static std::string getInput()
	{
		char* buffer = new char[256];
		std::cin.getline(buffer, 256);
		std::cin.clear();
		auto string = std::string(buffer);
		delete[] buffer;

		return string;
	}

	static std::string getInput(boost::asio::ip::tcp::socket* _socket)
	{
		boost::asio::streambuf b;
		read_until(*_socket, b, "\n");
		std::istream is(&b);
		std::string line;
		std::getline(is, line);
		
		return line;
	}

	static void write(const std::string& _message, boost::asio::ip::tcp::socket* _socket)
	{
		const auto finalMessage = std::string(_message + "\n");
		boost::asio::write(*_socket, boost::asio::buffer(finalMessage));
	}
};
