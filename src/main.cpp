#include <asio.hpp>
#include <iostream>
#include <iomanip>
#include "endian/endian.h"
#include "packet.h"

int main()
{
	Packet packet = Packet(0);

	std::cout << packet.readVarInt() << std::endl;

	return 0;
}
