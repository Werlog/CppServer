#include "event/events/playerjoinedevent.h"

PlayerJoinedEvent::PlayerJoinedEvent(std::shared_ptr<Player> player)
	: Event(EventType::PLAYER_JOINED_EVENT)
{
	this->joinedPlayer = player;
}

const std::shared_ptr<Player> PlayerJoinedEvent::getPlayer() const
{
	return joinedPlayer;
}
