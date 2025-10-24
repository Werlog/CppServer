#include <asio.hpp>
#include <iostream>
#include <iomanip>
#include "endian/endian.h"

using asio::ip::tcp;

void printHexBytes(int number) {
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&number);

    std::cout << "Hex bytes of " << number << ": ";
    for (size_t i = 0; i < sizeof(number); ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(2)
            << static_cast<int>(bytePtr[i]) << " ";
    }
    std::cout << std::dec << std::endl; // switch back to decimal
}

int main()
{
    int number = 2147483647;
    printHexBytes(number);

    printHexBytes(endian::nativeToBigEndian(number));
	return 0;
}
