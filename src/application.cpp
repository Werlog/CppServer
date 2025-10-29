#include "application.h"
#include <thread>
#include <chrono>

Application::Application()
	: server(25565)
{
	server.startServer();
}

void Application::mainLoop()
{
	while (true)
	{
		server.update();

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}
