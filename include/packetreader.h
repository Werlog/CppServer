#pragma once

#include <vector>

class Connection;

class PacketReader
{
public:
	PacketReader(Connection& connection);

	void onReceiveData(const std::array<char, 512>& data, size_t bytesTransferred);
private:
	Connection& connection;
	std::vector<char> receiveBuffer;

	void readPackets();
};
