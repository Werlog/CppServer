#pragma once

#include <vector>

class Client;

class PacketReader
{
public:
	PacketReader(Client& connection);

	void onReceiveData(const std::array<char, 512>& data, size_t bytesTransferred);
private:
	Client& connection;
	std::vector<char> receiveBuffer;

	void readPackets();
};
