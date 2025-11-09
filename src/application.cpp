#include "application.h"
#include <thread>
#include <chrono>
#include "command/commandHandlers/joincommandhandler.h"
#include "event/eventHandlers/joinedeventhandler.h"
#include "event/eventHandlers/disconnectedhandler.h"

Application::Application()
	: server(25565, *this)
{
	this->maxPlayers = 20;
	server.startServer();
}

void Application::run()
{
	initCommandBus();
	initEventBus();

	while (true)
	{
		server.update();
		eventBus.dispatchEvents(*this);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

std::unordered_map<uint32_t, std::shared_ptr<Player>>& Application::getPlayers()
{
	return players;
}

CommandResult Application::submitCommand(const Command& command)
{
	return commandBus.execute(command, *this);
}

void Application::submitEvent(std::shared_ptr<Event> event)
{
	eventBus.submitEvent(std::move(event));
}

void Application::removePlayer(uint32_t playerId)
{
	auto it = players.find(playerId);
	if (it == players.end())
		return;

	players.erase(it);
}

std::shared_ptr<Player> Application::getPlayerById(uint32_t playerId)
{
	auto it = players.find(playerId);
	if (it == players.end())
		return nullptr;

	return it->second;
}

Server& Application::getServer()
{
	return server;
}

uint32_t Application::getMaxPlayers() const
{
	return maxPlayers;
}

void Application::initCommandBus()
{
	commandBus.registerHandler(CommandType::JOIN_COMMAND, std::move(std::make_unique<JoinCommandHandler>()));
}

void Application::initEventBus()
{
	eventBus.registerHandler(EventType::PLAYER_JOINED_EVENT, std::move(std::make_unique<JoinedEventHandler>()));
	eventBus.registerHandler(EventType::CLIENT_DISCONNECTED_EVENT, std::move(std::make_unique<DisconnectedEventHandler>()));
}
