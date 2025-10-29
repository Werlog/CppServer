#include "connection.h"
#include <iostream>

Connection::Connection(asio::io_context& serverContext, asio::ip::tcp::socket socket)
	: serverContext(serverContext), socket(std::move(socket)), packetReader(*this)
{
	beginReadData();
}

Connection::~Connection()
{
	socket.close();
}

void Connection::setReceivePacketCallback(const std::function<void(Packet&)>& callback)
{
	this->receiveCallback = callback;
}

void Connection::onPacketRead(Packet& packet)
{
	if (receiveCallback)
		receiveCallback(packet);
}

void Connection::beginReadData()
{
	socket.async_receive(asio::buffer(readBuffer), [this](std::error_code ec, size_t bytesTransferred)
	{
		if (!ec)
		{
			packetReader.onReceiveData(readBuffer, bytesTransferred);
		}
		else
		{
			std::cout << "Failed to read from socket: " << ec.message() << std::endl;
			return;
		}

		beginReadData();
	});
}

