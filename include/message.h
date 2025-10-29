#pragma once

#include <memory>
#include <stdint.h>
#include "packet.h"

struct Message
{
	uint32_t fromClientId;
	std::unique_ptr<Packet> packet;
};
