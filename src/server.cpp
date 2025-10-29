#include "server.h"
#include <iostream>

Server::Server(uint32_t serverPort)
	: acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
{
	this->currentClientId = 0;
}

void Server::update(uint32_t maxPackets)
{
	uint32_t processed = 0;
	while (processed < maxPackets && !messageQueue.empty())
	{
		Message message = messageQueue.pop_front();

		std::cout << "Processing packet from client " << message.fromClientId << " with ID " << message.packet->getPacketId() << std::endl;
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

void Server::receiveMessage(Message message)
{
	messageQueue.push_back(std::move(message));
}

void Server::onClientDisconnected(uint32_t clientId)
{
	auto it = clients.find(clientId);
	if (it == clients.end())
		return;

	std::cout << clientId << " has disconnected." << std::endl;

	clients.erase(it);
}

void Server::beginAcceptClient()
{
	acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
	{
		if (!ec)
		{
			auto idk = socket.remote_endpoint();

			std::shared_ptr<Client> client = std::make_shared<Client>(context, std::move(socket), getNextClientId());

			client->setReceivePacketCallback([this](Message message) { receiveMessage(std::move(message)); });
			client->setDisconnectCallback([this](uint32_t clientId) { onClientDisconnected(clientId); });

			clients.insert({ client->getClientId(), client });

			std::cout << idk << " has connected and has been assigned to client id " << client->getClientId() << std::endl;
		}
		else
		{
			std::cerr << "Could not accept client: " << ec.message() << std::endl;
		}

		beginAcceptClient();
	});
}

uint32_t Server::getNextClientId()
{
	return ++currentClientId;
}
