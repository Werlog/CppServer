#pragma once

#include "event.h"

class EventHandler
{
public:
	virtual void handle(const Event& event) = 0;
};
