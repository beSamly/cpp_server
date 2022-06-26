#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {
	class Login : public IPacketHandler
	{
	public:
		void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len);
	};
}

