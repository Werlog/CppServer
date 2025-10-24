#include "packet.h"
#include <iostream>
#include <string>

#include "endian/endian.h"
#include "util/varintutil.h"

Packet::Packet(uint32_t packetId)
{
	this->packetId = packetId;
	this->readBytes = 0;
}

void Packet::writeByte(char value)
{
	writeData(&value, sizeof(char));
}

void Packet::writeInt(int32_t value)
{
	value = endian::nativeToBigEndian(value);

	writeData(reinterpret_cast<char*>(&value), sizeof(int32_t));
}

void Packet::writeVarInt(int32_t value)
{
	constexpr uint32_t SEGMENT_BITS = 0x7F;
	constexpr uint32_t CONTINUE_BIT = 0x80;

	uint32_t val = static_cast<uint32_t>(value);

	while (true)
	{
		if ((val & ~SEGMENT_BITS) == 0)
		{
			uint8_t byte = static_cast<uint8_t>(val);
			writeData(reinterpret_cast<char*>(&byte), 1);
			return;
		}

		uint8_t byte = static_cast<uint8_t>((val & SEGMENT_BITS) | CONTINUE_BIT);
		writeData(reinterpret_cast<char*>(&byte), 1);

		val >>= 7;
	}
}

char Packet::readByte()
{
	char value = 0;

	readData(&value, sizeof(char));

	return value;
}

int32_t Packet::readInt()
{
	int32_t value;

	readData(reinterpret_cast<char*>(&value), sizeof(int32_t));

	return value;
}

int32_t Packet::readVarInt()
{
	uint32_t size = 0;
	int32_t value = varint::readVarInt(buffer.data() + readBytes, &size);

	readBytes += size;

	return value;
}

uint32_t Packet::getPacketLength()
{
	return (uint32_t)buffer.size();
}

void Packet::writeData(const char* data, size_t size)
{
	size_t bufSize = buffer.size();

	buffer.resize(buffer.size() + size);
	std::memcpy(buffer.data() + bufSize, data, size);
}

void Packet::readData(char* destination, size_t size)
{
	if (readBytes + size >= buffer.size())
	{
		size_t remaining = buffer.size() - readBytes;

		throw std::out_of_range("Could not read data from packet, remaining buffer size is " + std::to_string(remaining) + " which is not enough to read " + std::to_string(size) + " bytes.");
	}

	std::memcpy(destination, buffer.data() + readBytes, size);

	readBytes += size;
}
