#include "application.h"
#include <thread>
#include <chrono>
#include "command/commandHandlers/joincommandhandler.h"

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

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
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

void Application::submitEvent(const Event& event)
{
	eventBus.handleEvent(event);
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

}
