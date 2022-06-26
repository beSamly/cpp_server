#pragma once
#include "IPacketHandler.h"
#include "ClientSession.h"

bool Handle_INVALID(ClientSessionRef& session, BYTE* buffer, int32 len);

class PacketManager
{
private:
	std::vector<IPacketHandler*> _handlers;

public:
	PacketManager();
	~PacketManager();
	void Init();
	
	void HandlePacket(ClientSessionRef& session, int16 packetId, BYTE* buffer, int32 len);
};

