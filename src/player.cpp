#include "player.h"

Player::Player(uint32_t playerId, const std::string& playerName)
{
	this->playerId = playerId;
	this->playerName = playerName;
	this->position = glm::vec3(0);
}

void Player::setPosition(glm::vec3 position)
{
	this->position = position;
}

const std::string& Player::getPlayerName() const
{
	return playerName;
}

uint32_t Player::getPlayerId() const
{
	return playerId;
}
