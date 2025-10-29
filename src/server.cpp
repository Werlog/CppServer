#include "server.h"
#include <iostream>

Server::Server(uint32_t serverPort)
	: acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
{

}

void Server::update(uint32_t maxPackets)
{
	uint32_t processed = 0;
	while (processed < maxPackets && !packetQueue.empty())
	{
		Packet packet = packetQueue.pop_front();

		std::cout << "Processing packet with ID: " << packet.getPacketId() << std::endl;
	}
}

bool Server::startServer()
{
	try
	{
		beginAcceptClient();

		contextThread = std::thread([this]() { context.run(); });

		std::cout << "Server started" << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cerr << "Could not start the server: " << ex.what() << "\n";
		return false;
	}

	return true;
}

bool Server::stopServer()
{
	return false;
}

void Server::receivePacket(Packet& packet)
{
	packetQueue.push_back(std::move(packet));
}

void Server::beginAcceptClient()
{
	acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
	{
		if (!ec)
		{
			std::cout << "Incoming connection from " << socket.remote_endpoint() << "\n";

			std::shared_ptr<Connection> connection = std::make_shared<Connection>(context, std::move(socket));

			connection->setReceivePacketCallback([this](Packet& packet) { receivePacket(packet); });

			connections.push_back(connection);
		}
		else
		{
			std::cerr << "Could not accept client: " << ec.message() << std::endl;
		}

		beginAcceptClient();
	});
}
