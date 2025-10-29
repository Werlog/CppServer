#include "packet.h"
#include <iostream>
#include <string>

#include "endian/endian.h"
#include "util/varintutil.h"

Packet::Packet(uint32_t packetId)
{
	this->packetId = packetId;
	this->readBytes = 0;

	writeVarInt(packetId);
}

Packet::Packet(const char* data, size_t size)
{
	writeData(data, size);
	this->readBytes = 0;
	this->packetId = readVarInt();
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
	char varIntBytes[5];
	int32_t size = 0;

	varint::writeVarInt(value, varIntBytes, &size);

	writeData(varIntBytes, size);
}

void Packet::writeString(const std::string& value)
{
	writeVarInt(value.length());

	writeData(value.data(), value.length());
}

void Packet::writeUShort(uint16_t value)
{
	value = endian::nativeToBigEndian(value);

	writeData(reinterpret_cast<char*>(&value), sizeof(uint16_t));
}

void Packet::writeLong(int64_t value)
{
	value = endian::nativeToBigEndian(value);

	writeData(reinterpret_cast<char*>(&value), sizeof(int64_t));
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

	value = endian::bigEndianToNative(value);

	return value;
}

int32_t Packet::readVarInt()
{
	uint32_t size = 0;
	int32_t value = varint::readVarInt(buffer.data() + readBytes, &size);

	readBytes += size;

	return value;
}

std::string Packet::readString()
{
	int32_t length = readVarInt();

	std::string value = std::string(length, '@');
	readData(value.data(), length);

	return value;
}

uint16_t Packet::readUShort()
{
	uint16_t value;

	readData(reinterpret_cast<char*>(&value), sizeof(uint16_t));

	value = endian::bigEndianToNative(value);

	return value;
}

int64_t Packet::readLong()
{
	int64_t value;

	readData(reinterpret_cast<char*>(&value), sizeof(int64_t));

	value = endian::bigEndianToNative(value);

	return value;
}

uint32_t Packet::getPacketLength() const
{
	return (uint32_t)buffer.size();
}

uint32_t Packet::getPacketId() const
{
	return packetId;
}

const char* Packet::getData() const
{
	return buffer.data();
}

void Packet::writeData(const char* data, size_t size)
{
	size_t bufSize = buffer.size();

	buffer.resize(buffer.size() + size);
	std::memcpy(buffer.data() + bufSize, data, size);
}

void Packet::readData(char* destination, size_t size)
{
	if (readBytes + size > buffer.size())
	{
		size_t remaining = buffer.size() - readBytes;

		throw std::out_of_range("Could not read data from packet, remaining buffer size is " + std::to_string(remaining) + " which is not enough to read " + std::to_string(size) + " bytes.");
	}

	std::memcpy(destination, buffer.data() + readBytes, size);

	readBytes += size;
}
