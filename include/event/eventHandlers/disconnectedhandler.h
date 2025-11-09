#pragma once

#include "../eventhandler.h"
#include "../event.h"

class DisconnectedEventHandler : public EventHandler
{
public:
	virtual void handle(std::shared_ptr<const Event> event, Application& application) override;
};
