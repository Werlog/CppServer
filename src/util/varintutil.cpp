#include "util/varintutil.h"

namespace varint
{
	constexpr int SEGMENT_BITS = 0x7f;
	constexpr int CONTINUE_BIT = 0x80;
	constexpr int MAX_VARINT_LENGTH = 5;

	int32_t readVarInt(const char* source, uint32_t* varIntSize)
	{
		int32_t value = 0;
		int32_t position = 0;
		char currentByte = 0;

		while (true)
		{
			currentByte = source[position];

			value |= (currentByte & SEGMENT_BITS) << (position * 7);

			if ((currentByte & CONTINUE_BIT) == 0) break;

			position++;

			if (position >= MAX_VARINT_LENGTH) break;
		}

		if (varIntSize != nullptr)
			*varIntSize = position + 1;

		return value;
	}

	void writeVarInt(int32_t value, char* destination, int32_t* varIntSize)
	{
		uint32_t val = static_cast<uint32_t>(value);

		int32_t position = 0;

		while (true)
		{
			if ((val & ~SEGMENT_BITS) == 0)
			{
				uint8_t byte = static_cast<uint8_t>(val);
				*(destination + position) = byte;
				position++;
				break;
			}

			uint8_t byte = static_cast<uint8_t>((val & SEGMENT_BITS) | CONTINUE_BIT);
			*(destination + position) = byte;

			val >>= 7;
			position++;
		}

		*varIntSize = position;
	}

	bool isCompleteVarInt(const char* source, int32_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			char byte = source[i];

			if ((byte & CONTINUE_BIT) == 0)
				return true;

			if (i + 1 >= MAX_VARINT_LENGTH)
				return true;
		}

		return false;
	}
}