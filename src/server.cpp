#include "server.h"
#include <iostream>
#include "packethandler/handlers/statushandler.h"
#include "packethandler/handlers/loginhandler.h"
#include "packethandler/handlers/playhandler.h"
#include "logger.h"
#include "application.h"
#include "event/events/clientdisconnectedevent.h"

Server::Server(uint32_t serverPort, Application& application)
	: application(application), acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), serverPort))
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
				DEBUG_LOG("No packet handler exists for connection state " + std::to_string(client->getConnectionState()));
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

		logger::logInfo("Server started.");
	}
	catch (std::exception& ex)
	{
		logger::logError("Failed to start the server" + std::string(ex.what()));
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

void Server::onClientDisconnected(uint32_t clientId)
{
	auto it = clients.find(clientId);
	if (it == clients.end())
		return;

	application.submitEvent(std::make_shared<ClientDisconnectedEvent>(clientId));

	DEBUG_LOG("Client " + std::to_string(clientId) + " has disconnected");
	clients.erase(it);
}

void Server::disconnectClient(uint32_t clientId)
{
	auto it = clients.find(clientId);
	if (it == clients.end())
		return;

	it->second->disconnect();
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
	packetHandlers.insert({ ConnectionState::HANDSHAKING, std::make_unique<HandshakingHandler>(*this, application) });
	packetHandlers.insert({ ConnectionState::STATUS, std::make_unique<StatusHandler>(*this, application) });
	packetHandlers.insert({ ConnectionState::LOGIN, std::make_unique<LoginHandler>(*this, application) });
	packetHandlers.insert({ ConnectionState::PLAY, std::make_unique<PlayHandler>(*this, application) });
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
			DEBUG_LOG(idk.address().to_string() + " has connected and has been assigned to client id " + std::to_string(client->getClientId()));
		}
		else
		{
			logger::logWarning("Could not accept client: " + ec.message());
		}

		beginAcceptClient();
	});
}

uint32_t Server::getNextClientId()
{
	return ++currentClientId;
}
