#pragma once

#include <stdint.h>

namespace varint
{
	int32_t readVarInt(const char* source, uint32_t* varIntSize);
	void writeVarInt(int32_t value, char* destination, int32_t* varIntSize);
	bool isCompleteVarInt(const char* source, int32_t size);
}
