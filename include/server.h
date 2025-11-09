#pragma once

#include <asio.hpp>
#include "util/tsqueue.h"
#include "packet.h"
#include <stdint.h>
#include <thread>
#include "client.h"
#include <unordered_map>
#include "packethandler/handlers/handshakinghandler.h"

class Application;

class Server
{
public:
	Server(uint32_t serverPort, Application& application);

	void update(uint32_t maxPackets = -1);

	bool startServer();
	bool stopServer();

	void receiveMessage(Message message);
	void onClientDisconnected(uint32_t clientId);

	void disconnectClient(uint32_t clientId);

	void send(std::unique_ptr<Packet> packet, uint32_t clientId);
	void sendToAllPlaying(std::unique_ptr<Packet> packet, uint32_t exceptClientId = -1);

	std::shared_ptr<Client> getClientById(uint32_t clientId);
private:
	Application& application;

	std::unordered_map<uint32_t, std::shared_ptr<Client>> clients;
	std::unordered_map<ConnectionState, std::unique_ptr<PacketHandler>> packetHandlers;
	tsqueue<Message> inMessageQueue;
	uint32_t currentClientId;

	asio::io_context context;
	std::thread contextThread;
	asio::ip::tcp::acceptor acceptor;

	void registerPacketHandlers();

	void beginAcceptClient();
	uint32_t getNextClientId();
};
