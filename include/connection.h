#pragma once

#include <asio.hpp>
#include <functional>
#include "packet.h"
#include "packetreader.h"

enum ConnectionState : unsigned char
{
	HANDSHAKING,
	LOGIN,
	STATUS,
	PLAY
};

class Connection
{
public:
	Connection(asio::io_context& serverContext, asio::ip::tcp::socket socket);
	~Connection();

	void setReceivePacketCallback(const std::function<void(Packet&)>& callback);

	void onPacketRead(Packet& packet);
private:
	asio::ip::tcp::socket socket;
	asio::io_context& serverContext;

	PacketReader packetReader;

	std::function<void(Packet&)> receiveCallback;
	std::array<char, 512> readBuffer;

	void beginReadData();
};
