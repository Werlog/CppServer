#pragma once

#include <string>

namespace logger
{
	enum LogMessageType : unsigned char
	{
		LOG_INFO,
		LOG_WARNING,
		LOG_DEBUG,
		LOG_ERROR,
	};

	void log(const std::string& text, LogMessageType messageType);

	void logInfo(const std::string& text);

	void logError(const std::string& text);

	void logWarning(const std::string& text);

	std::string getLogTypeString(LogMessageType messageType);
}

#if PRODUCTION_BUILD == 0
#define DEBUG_LOG(text) logger::log((text), logger::LogMessageType::LOG_DEBUG);
#else
#define DEBUG_LOG(text)
#endif