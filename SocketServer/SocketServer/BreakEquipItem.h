#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {

	class BreakEquipItem : public IPacketHandler
	{
	public:
		void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len);
	};
}

