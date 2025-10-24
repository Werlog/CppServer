#include "endian/endian.h"

#include <stdint.h>
#include <type_traits>
#include <algorithm>

namespace endian
{
	bool isMachineLittleEndian()
	{
		int num = 1;

		return *(char*)&num == 1;
	}
}
