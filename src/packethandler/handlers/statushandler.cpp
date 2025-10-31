#include "packethandler/handlers/statushandler.h"
#include <iostream>
#include "server.h"

StatusHandler::StatusHandler(Server& server)
	: PacketHandler(server)
{
	registerHandlerFunctions();
}

void StatusHandler::registerHandlerFunctions()
{
	handlerFunctions.insert({ 0, PACKET_HANDLER_BIND(&StatusHandler::requestHandler) });
	handlerFunctions.insert({ 1, PACKET_HANDLER_BIND(&StatusHandler::pingHandler) });
}

void StatusHandler::requestHandler(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	std::string jesonne = "{\"version\":{\"name\":\"1.12.2\",\"protocol\":340},\"players\":{\"max\":40,\"online\":0},\"description\":{\"text\":\"I hate JavaScript!\"},\"favicon\":\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAMAAACdt4HsAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAACEUExURfDbT/8AAC8wMG9pOjIzMC8xMPLdTzAyML2uRufTTtjGS/HcT/PdTzAxMPHbT6qdQ2BbNzEzMOXRTY2EP4R7PevWTjg4MXx0POjUTvLcT+bSTYh/Po2DPzEyMIB4PcCwR0A/MtXDS/PeUFxYNzQ1MGJdOD09MuLPTS8wLzk5MaKWQt3KTJBkrhgAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAAYdEVYdFNvZnR3YXJlAFBhaW50Lk5FVCA1LjEuN4vW9zkAAAC2ZVhJZklJKgAIAAAABQAaAQUAAQAAAEoAAAAbAQUAAQAAAFIAAAAoAQMAAQAAAAIAAAAxAQIAEAAAAFoAAABphwQAAQAAAGoAAAAAAAAAYAAAAAEAAABgAAAAAQAAAFBhaW50Lk5FVCA1LjEuNwADAACQBwAEAAAAMDIzMAGgAwABAAAAAQAAAAWgBAABAAAAlAAAAAAAAAACAAEAAgAEAAAAUjk4AAIABwAEAAAAMDEwMAAAAAAlR56NozS1xQAAAcJJREFUWEftldl2wyAMRJ2UpEua7ume7nv///9qiQEksA04fcy8WAxzx8Qnx262+i9NJhgqpJhJfUOEVDckQGVDR7yqoTNc0dATLW7oDRY2DMSKGgZDBQ2ZSLZh08CmRyzgB0NF/ECskO8NFvM90Qq+M1zFd8Qr+QSo5iNkBK+gUbzARvIeHM0zOp1KfseQZnMs82phwe8yziqtMMQbt5Dag5mRLADpZM2ciMdP2AfoxW5GdHs6BM3ADhaHSx6OODEs5l0DU/a2x8ac8JAReDTY0e6c2ktGhIESY7nUbf1hsFkg5sNtfcMZ7+ZleXFu32DOaZkTePnDQ4NZsjEkx6snJxpyz8LzqqC8IfC6QDdcwEwl+KhAN6xgxpJ8XECbl9ZrBS+S4pMC3r6yrrmGp6T5tMAGrD2DJRXxHQWyAY5QzOugueELhZQf5Hn30rzlnP3j0WuEB4qxnxQ4PmzyZO7a6d6O/gy0WPMiSPHGPCweMS1a8wnz+vll/kpvmHbmdJDjmzcbDWIXM8QN7Ht5Ps7i2GmD/rYIPsq+w0wb4LOi5QdSregBQJ+wWBGi+VarL0p94/heP/x5nP7SnDBbjVTT/AEjIQ07IR77CQAAAABJRU5ErkJggg==\"}";

	std::unique_ptr<Packet> responsePacket = std::make_unique<Packet>(0);
	responsePacket->writeString(jesonne);

	std::shared_ptr<Client> client = server.getClientById(message.clientId);

	if (client != nullptr)
		client->sendPacket(std::move(responsePacket));
}

void StatusHandler::pingHandler(Message message)
{
	std::unique_ptr<Packet> packet = std::move(message.packet);

	int64_t val = packet->readLong();

	std::unique_ptr<Packet> responsePacket = std::make_unique<Packet>(1);
	responsePacket->writeLong(val);


	std::shared_ptr<Client> client = server.getClientById(message.clientId);
	if (client != nullptr)
		client->sendPacket(std::move(responsePacket));
}
