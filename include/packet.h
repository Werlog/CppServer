#pragma once

#include <stdint.h>
#include <vector>

struct PackerHeader
{
	uint32_t packetLength;
	uint32_t packetId;
};

class Packet
{
public:

	Packet(uint32_t packetId);

	void writeByte(char value);
	void writeInt(int32_t value);
	void writeVarInt(int32_t value);

	char readByte();
	int32_t readInt();
	int32_t readVarInt();

	uint32_t getPacketLength();
private:
	std::vector<char> buffer;

	uint32_t packetId;
	uint32_t readBytes;

	void writeData(const char* data, size_t size);
	void readData(char* destination, size_t size);
};
