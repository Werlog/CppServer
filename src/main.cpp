#include <asio.hpp>
#include <iostream>
#include <iomanip>
#include "endian/endian.h"
#include "packet.h"

int main()
{
	Packet packet = Packet(0);

	packet.writeVarInt(-2147483648);

	std::cout << packet.readVarInt() << std::endl;

	return 0;
}
