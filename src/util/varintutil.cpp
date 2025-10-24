#include "util/varintutil.h"

namespace varint
{
	constexpr int SEGMENT_BITS = 0x7f;
	constexpr int CONTINUE_BIT = 0x80;

	int32_t readVarInt(const char* source, uint32_t* varIntSize)
	{
		int32_t value = 0;
		int32_t position = 0;
		char currentByte = 0;

		while (true)
		{
			currentByte = *(source + position);

			value |= (currentByte & SEGMENT_BITS) << (position * 7);

			if ((currentByte & CONTINUE_BIT) == 0) break;

			position++;

			if (position >= 5) break;
		}

		if (varIntSize != nullptr)
			*varIntSize = position;

		return value;
	}
}