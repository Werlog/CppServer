#pragma once

#include <string>

struct CommandResult
{
	bool success;
	std::string message;

	static CommandResult ok()
	{
		return CommandResult{ true, "Success" };
	}
	static CommandResult failure(const std::string& message)
	{
		return CommandResult{ false, message };
	}

	operator bool() const
	{
		return success;
	}
};
