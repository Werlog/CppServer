#include "logger.h"
#include <chrono>
#include <iostream>
#include <iomanip>

void logger::log(const std::string& text, LogMessageType messageType)
{
	auto now = std::chrono::system_clock::now();
	auto timeNow = std::chrono::system_clock::to_time_t(now);

	std::cout << "[" << std::put_time(std::localtime(&timeNow), "%H:%M:%S") << "] " << getLogTypeString(messageType) << ": " << text << "\n";
}

void logger::logInfo(const std::string& text)
{
	logger::log(text, LOG_INFO);
}

void logger::logError(const std::string& text)
{
	logger::log(text, LOG_ERROR);
}

void logger::logWarning(const std::string& text)
{
	logger::log(text, LOG_WARNING);
}

void logger::logChat(const std::string& text)
{
	logger::log(text, LOG_CHAT);
}

std::string logger::getLogTypeString(LogMessageType messageType)
{
	switch (messageType)
	{
	case LOG_DEBUG:
		return "[DEBUG]";
	case LOG_WARNING:
		return "[WARN]";
	case LOG_ERROR:
		return "[ERROR]";
	case LOG_CHAT:
		return "[CHAT]";
	default:
		return "[INFO]";
	}
}
