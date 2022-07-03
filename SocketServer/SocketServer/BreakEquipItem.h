#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {

	class BreakEquipItem : public IPacketHandler
	{
	public:
		bool Validate(ClientSessionRef& session, BYTE* buffer, int32 len) override;

		void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len) override;
	};
}


