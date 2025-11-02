#pragma once

enum CommandType : unsigned char
{

};

class Command
{
public:
	Command(CommandType type);

	CommandType getCommandType() const;
private:
	CommandType type;
};
