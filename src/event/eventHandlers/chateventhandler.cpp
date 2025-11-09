#include "event/eventHandlers/chateventhandler.h"
#include "event/events/chatevent.h"
#include "packet.h"
#include "application.h"

void ChatEventHandler::handle(std::shared_ptr<const Event> event, Application& application)
{
	auto chatEvent = std::dynamic_pointer_cast<const ChatEvent>(event);

	std::unique_ptr<Packet> packet = std::make_unique<Packet>(0x0F);
	packet->writeString("{\"text\":\"" + chatEvent->message + "\"}");
	packet->writeByte(chatEvent->messageType);

	if (chatEvent->broadcast)
	{
		application.getServer().sendToAllPlaying(std::move(packet));
	}
	else
	{
		application.getServer().send(std::move(packet), chatEvent->toClientId);
	}
}
