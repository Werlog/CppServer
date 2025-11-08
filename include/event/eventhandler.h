#pragma once

#include "event.h"
#include <memory>

class Application;

class EventHandler
{
public:
	virtual void handle(const std::shared_ptr<const Event> event, Application& application) = 0;
};
