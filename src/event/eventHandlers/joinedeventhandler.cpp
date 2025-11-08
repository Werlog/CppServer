#include "event/eventHandlers/joinedeventhandler.h"
#include "logger.h"
#include "event/events/playerjoinedevent.h"
#include "application.h"

void JoinedEventHandler::handle(std::shared_ptr<const Event> event, Application& application)
{
	auto joinedEvent = std::dynamic_pointer_cast<const PlayerJoinedEvent>(event);

	std::shared_ptr<Client> client = application.getServer().getClientById(joinedEvent->getPlayer()->getPlayerId());
	if (client == nullptr)
		return;

	std::unique_ptr<Packet> packet = std::make_unique<Packet>(0x02);
	packet->writeString("5c063efe-7550-4d35-968d-e93b5a7fb008");
	packet->writeString(joinedEvent->getPlayer()->getPlayerName());
	
	client->sendPacket(std::move(packet));
	client->setConnectionState(ConnectionState::PLAY);

	std::unique_ptr<Packet> joinedGame = std::make_unique<Packet>(0x23);
	joinedGame->writeInt(1);
	joinedGame->writeByte(0);
	joinedGame->writeInt(0);
	joinedGame->writeByte(1);
	joinedGame->writeByte(40);
	joinedGame->writeString("default");
	joinedGame->writeByte(0);

	client->sendPacket(std::move(joinedGame));

	std::unique_ptr<Packet> positionAndLook = std::make_unique<Packet>(0x2F);
	positionAndLook->writeDouble(0);
	positionAndLook->writeDouble(64);
	positionAndLook->writeDouble(0);
	positionAndLook->writeFloat(0);
	positionAndLook->writeFloat(0);
	positionAndLook->writeByte(0);
	positionAndLook->writeVarInt(2);

	client->sendPacket(std::move(positionAndLook));
}
