#pragma once

#include "../event.h"
#include <memory>
#include "../../player.h"

class PlayerJoinedEvent : public Event
{
public:

	PlayerJoinedEvent(std::shared_ptr<Player> player);

	const std::shared_ptr<Player> getPlayer() const;
private:
	std::shared_ptr<Player> joinedPlayer;
};
