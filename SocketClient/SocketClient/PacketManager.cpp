#include "pch.h"
#include "PacketManager.h"
#include "PacketId.h"
#include "IPacketHandler.h"
#include "LoginResponse.h"
#include "PacketHeader.h"

PacketManager::PacketManager()
{
	Init();
}

PacketManager::~PacketManager()
{
}

void PacketManager::Init() {
	_handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
	_handlers[PacketId::LOGIN_RES] = dynamic_cast<IPacketHandler*>(new PacketHandler::LoginResponse());

}

void PacketManager::HandlePacket(ServerSessionRef& session, int16 packetId, BYTE* buffer, int32 len) {

	IPacketHandler* packetHandler = _handlers[packetId];
	_handlers[packetId]->HandlePacket(session, buffer, len);
}