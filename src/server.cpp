#include "server.h"
#include <iostream>
#include "packethandler/handlers/statushandler.h"

Server::Server(uint32_t serverPort)
	: acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
{
	this->currentClientId = 0;

	registerPacketHandlers();
}

void Server::update(uint32_t maxPackets)
{
	uint32_t processed = 0;
	while (processed < maxPackets && !inMessageQueue.empty())
	{
		Message message = inMessageQueue.pop_front();

		std::shared_ptr<Client> client = getClientById(message.clientId);
		if (client != nullptr)
		{
			auto it = packetHandlers.find(client->getConnectionState());
			if (it == packetHandlers.end())
			{
				std::cout << "No packet handler exists for connection state \"" << std::to_string(client->getConnectionState()) << "\"" << std::endl;
				continue;
			}
			it->second->handleMessage(std::move(message));
		}
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
	inMessageQueue.push_back(std::move(message));
}

void Server::sendMessage(Message message)
{
	outMessageQueue.push_back(std::move(message));
}

void Server::onClientDisconnected(uint32_t clientId)
{
	auto it = clients.find(clientId);
	if (it == clients.end())
		return;

	std::cout << clientId << " has disconnected." << std::endl;

	clients.erase(it);
}

std::shared_ptr<Client> Server::getClientById(uint32_t clientId)
{
	auto it = clients.find(clientId);
	if (it == clients.end())
		return nullptr;

	return it->second;
}

void Server::registerPacketHandlers()
{
	packetHandlers.insert({ ConnectionState::HANDSHAKING, std::make_unique<HandshakingHandler>(*this) });
	packetHandlers.insert({ ConnectionState::STATUS, std::make_unique<StatusHandler>(*this) });
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
