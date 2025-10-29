#pragma once

#include <memory>
#include <stdint.h>
#include "packet.h"

struct Message
{
	uint32_t clientId;
	std::unique_ptr<Packet> packet;
};
