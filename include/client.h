#pragma once

#include <asio.hpp>
#include <functional>
#include "packet.h"
#include "packetreader.h"
#include "message.h"

enum ConnectionState : unsigned char
{
	HANDSHAKING,
	LOGIN,
	STATUS,
	PLAY
};

class Client
{
public:
	Client(asio::io_context& serverContext, asio::ip::tcp::socket socket, uint32_t clientId);
	~Client();

	void disconnect();

	void onPacketRead(std::unique_ptr<Packet> packet);

	void setReceivePacketCallback(const std::function<void(Message)>& callback);
	void setDisconnectCallback(const std::function<void(uint32_t)>& callback);
	void setConnectionState(ConnectionState newState);

	uint32_t getClientId() const;
	ConnectionState getConnectionState() const;
private:
	ConnectionState state;
	uint32_t clientId;

	asio::ip::tcp::socket socket;
	asio::io_context& serverContext;

	std::function<void(Message)> receiveCallback;
	std::function<void(uint32_t)> disconnectCallback;

	PacketReader packetReader;
	std::array<char, 512> readBuffer;

	void beginReadData();
};
