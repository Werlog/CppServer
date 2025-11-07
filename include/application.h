#pragma once

#include "server.h"
#include "command/commandbus.h"
#include "event/eventbus.h"
#include "player.h"

class Application
{
public:
	Application();

	void run();

	std::unordered_map<uint32_t, std::shared_ptr<Player>>& getPlayers();

	CommandResult submitCommand(const Command& command);
	void submitEvent(const Event& event);

	uint32_t getMaxPlayers() const;
private:
	uint32_t maxPlayers;
	std::unordered_map<uint32_t, std::shared_ptr<Player>> players;
	CommandBus commandBus;
	EventBus eventBus;
	Server server;

	void initCommandBus();
	void initEventBus();
};
