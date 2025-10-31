#include "client.h"
#include <iostream>
#include "util/varintutil.h"


Client::Client(asio::io_context& serverContext, asio::ip::tcp::socket socket, uint32_t clientId)
	: serverContext(serverContext), socket(std::move(socket)), packetReader(*this)
{
	this->clientId = clientId;
	this->state = ConnectionState::HANDSHAKING;
	this->sendInProgress = false;
	beginReadData();
}

Client::~Client()
{
	disconnect();
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

void Client::sendPacket(std::unique_ptr<Packet> packet)
{
	asio::post(socket.get_executor(), [this, p = std::move(packet)]() mutable
	{
		sendQueue.emplace_back(std::move(p));
		if (!sendInProgress)
			doSend();
	});
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

void Client::doSend()
{
	sendInProgress = true;

	std::unique_ptr<Packet> packet = std::move(sendQueue.front());
	sendQueue.pop_front();

	int32_t packetLength = packet->getPacketLength();
	sendData = std::vector<char>(packetLength);

	int32_t varintSize = 0;
	varint::writeVarInt(packetLength, sendData.data(), &varintSize);
	sendData.resize(sendData.size() + varintSize);

	std::memcpy(sendData.data() + varintSize, packet->getData(), packetLength);

	asio::async_write(socket, asio::buffer(sendData), [this](std::error_code ec, size_t bytesTransferred)
	{
		if (!ec)
		{
			if (!sendQueue.empty())
			{
				doSend();
			}
			else
			{
				sendInProgress = false;
			}
		}
		else
		{
			std::cerr << "Failed to transfer packet: " << ec.message() << std::endl;
		}
	});
}
