#pragma once

#include "../eventhandler.h"
#include "../event.h"

class JoinedEventHandler : public EventHandler
{
public:
	virtual void handle(std::shared_ptr<const Event> event, Application& application) override;
};
