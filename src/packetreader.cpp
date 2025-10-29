#include "packetreader.h"
#include "client.h"
#include "util/varintutil.h"
#include <iostream>

PacketReader::PacketReader(Client& connection)
	: connection(connection)
{

}

void PacketReader::onReceiveData(const std::array<char, 512>& data, size_t bytesTransferred)
{
	size_t bufSize = receiveBuffer.size();

	receiveBuffer.resize(bufSize + bytesTransferred);
	std::memcpy(receiveBuffer.data() + bufSize, data.data(), bytesTransferred);

	readPackets();
}

void PacketReader::readPackets()
{
	while (receiveBuffer.size() > 0)
	{
		int32_t packetLength = 0;
		uint32_t lengthSize = 0;

		if (varint::isCompleteVarInt(receiveBuffer.data(), receiveBuffer.size()))
		{
			packetLength = varint::readVarInt(receiveBuffer.data(), &lengthSize);
		}
		else break;

		if (receiveBuffer.size() >= packetLength + lengthSize)
		{
			std::unique_ptr<Packet> packet = std::make_unique<Packet>(receiveBuffer.data() + lengthSize, packetLength);

			connection.onPacketRead(std::move(packet));

			receiveBuffer.erase(receiveBuffer.begin(), receiveBuffer.begin() + packetLength + lengthSize);
		}
		else break;
	}
}
