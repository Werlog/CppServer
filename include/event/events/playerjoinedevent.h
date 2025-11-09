#pragma once

#include "../event.h"
#include <memory>
#include "../../player.h"

struct PlayerJoinedEvent : public Event
{
	std::shared_ptr<const Player> joinedPlayer;

	PlayerJoinedEvent(std::shared_ptr<const Player> player)
		: Event(EventType::PLAYER_JOINED_EVENT)
	{
		this->joinedPlayer = player;
	}
};
