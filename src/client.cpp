#include "client.h"
#include <iostream>
#include "util/varintutil.h"


Client::Client(asio::io_context& serverContext, asio::ip::tcp::socket socket, uint32_t clientId)
	: serverContext(serverContext), socket(std::move(socket)), packetReader(*this)
{
	this->clientId = clientId;
	this->state = ConnectionState::HANDSHAKING;
	beginReadData();
}

Client::~Client()
{
	socket.close();
}

void Client::setReceivePacketCallback(const std::function<void(Message)>& callback)
{
	this->receiveCallback = callback;
}

void Client::setDisconnectCallback(const std::function<void(uint32_t)>& callback)
{
	this->disconnectCallback = callback;
}

void Client::setConnectionState(ConnectionState newState)
{
	this->state = newState;
}

void Client::onPacketRead(std::unique_ptr<Packet> packet)
{
	if (receiveCallback)
	{
		Message message = Message{ clientId, std::move(packet) };
		receiveCallback(std::move(message));
	}
}

void Client::sendMessage(Message message)
{
	int32_t packetLength = message.packet->getPacketLength();
	std::vector<char> packetData = std::vector<char>(packetLength);

	int32_t varintSize = 0;
	varint::writeVarInt(packetLength, packetData.data(), &varintSize);
	packetData.resize(packetData.size() + varintSize);

	std::memcpy(packetData.data() + varintSize, message.packet->getData(), packetLength);

	socket.send(asio::buffer(packetData));
}

void Client::disconnect()
{
	socket.close();

	if (disconnectCallback)
		disconnectCallback(clientId);
}

uint32_t Client::getClientId() const
{
	return clientId;
}

ConnectionState Client::getConnectionState() const
{
	return state;
}

void Client::beginReadData()
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
			disconnect();
			return;
		}

		beginReadData();
	});
}
