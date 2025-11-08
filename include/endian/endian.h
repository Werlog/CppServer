namespace endian
{
	bool isMachineLittleEndian();

	template<typename T>
	T swapEndianness(T value)
	{
		static_assert(std::is_arithmetic<T>::value, "swapEndianness only supports arithmetic types");

		char bytes[sizeof(T)];
		std::memcpy(bytes, reinterpret_cast<char*>(&value), sizeof(T));
		std::reverse(bytes, bytes + sizeof(T));
		std::memcpy(&value, bytes, sizeof(T));

		return value;
	}

	template<typename T>
	T nativeToBigEndian(T value)
	{
		static_assert(std::is_arithmetic<T>::value, "nativeToBigEndian only supports arithmetic types");

		if (isMachineLittleEndian())
			return swapEndianness(value);

		return value;
	}

	template<typename T>
	T bigEndianToNative(T value)
	{
		static_assert(std::is_arithmetic<T>::value, "bigEndianToNative only supports arithmetic types");

		if (isMachineLittleEndian())
			return swapEndianness(value);

		return value;
	}
}
