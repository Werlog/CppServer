#pragma once

#include <stdint.h>

namespace varint
{
	int32_t readVarInt(const char* source, uint32_t* varIntSize);
}
