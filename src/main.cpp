#include <asio.hpp>
#include <iostream>
#include <iomanip>
#include "util/tsqueue.h"
#include "application.h"

int main()
{
	Application application;
	application.mainLoop();

	return 0;
}
