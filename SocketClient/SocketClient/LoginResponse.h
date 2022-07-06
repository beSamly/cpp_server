#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {

	class LoginResponse: public IPacketHandler
	{
	public:
		bool Validate(ServerSessionRef& session, BYTE* buffer, int32 len) override;

		void HandlePacket(ServerSessionRef& session, BYTE* buffer, int32 len) override;
	};
}