#pragma once

#include <glm/glm.hpp>
#include <stdint.h>
#include <string>

class Player
{
public:
	
	Player(uint32_t playerId, const std::string& playerName);

	void setPosition(glm::vec3 position);

	const std::string& getPlayerName() const;
	uint32_t getPlayerId() const;
private:
	std::string playerName;
	uint32_t playerId;
	glm::vec3 position;
};
