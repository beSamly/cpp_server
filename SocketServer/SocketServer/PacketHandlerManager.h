#pragma once
#include <stdint.h>
#include "IPacketHandler.h"
#include "LoginHandler.h"
#include "ClientSession.h"

enum : uint16
{
	C_LOGIN = 1,

};

bool Handle_INVALID(ClientSessionRef& session, BYTE* buffer, int32 len);

class PacketHandlerManager
{
public:
	static Vector<IPacketHandler*> handlers;

public:
	static void Init()
	{
		handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
		Vector<IPacketHandler*> handlers(UINT16_MAX, nullptr);
		handlers[C_LOGIN] = (IPacketHandler*)(new LoginHandler());

		//[](ClientSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
	}

	static void HandlePacket(ClientSessionRef session, int16 packetId, BYTE* buffer, int32 len) {

		if (handlers[packetId] == nullptr) {
			// TODO logging
			cout << "Invalid packet id received" << packetId << endl;
			return;
		}

		handlers[packetId]->HandlePacket(session, buffer, len);
	}
};

