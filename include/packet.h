#pragma once

#include <stdint.h>
#include <vector>
#include <string>

class Packet
{
public:

	Packet(uint32_t packetId);
	Packet(const char* data, size_t size);

	void writeByte(char value);
	void writeInt(int32_t value);
	void writeVarInt(int32_t value);
	void writeString(const std::string& value);
	void writeUShort(uint16_t value);

	char readByte();
	int32_t readInt();
	int32_t readVarInt();
	std::string readString();
	uint16_t readUShort();

	uint32_t getPacketLength() const;
	uint32_t getPacketId() const;
private:
	std::vector<char> buffer;

	uint32_t packetId;
	uint32_t readBytes;

	void writeData(const char* data, size_t size);
	void readData(char* destination, size_t size);
};
