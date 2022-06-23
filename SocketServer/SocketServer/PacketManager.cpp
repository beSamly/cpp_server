#include "pch.h"
#include "PacketManager.h"
#include "PacketHeader.h"
#include "PacketId.h"

bool Handle_INVALID(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

PacketManager::PacketManager()
{
	Init();
}

PacketManager::~PacketManager()
{
}

void PacketManager::Init() {
	_handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
	_handlers[PacketId::LOGIN_REQ] = (IPacketHandler*)(new LoginHandler());

	//[](ClientSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::LOGIN_REQ>(Handle_LOGIN_REQ, session, buffer, len); };
}

void PacketManager::HandlePacket(ClientSessionRef& session, int16 packetId, BYTE* buffer, int32 len) {

	if (_handlers[packetId] == nullptr) {
		// TODO logging
		cout << "Invalid packet id received" << packetId << endl;
		return;
	}

	_handlers[packetId]->HandlePacket(session, buffer, len);
}