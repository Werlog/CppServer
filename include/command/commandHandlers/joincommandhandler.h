#pragma once

#include "../commandhandler.h"

class JoinCommandHandler : public CommandHandler
{
public:
	virtual CommandResult handle(const Command& command, Application& application) override;
};
