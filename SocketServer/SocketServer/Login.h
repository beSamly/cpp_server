#pragma once
#include "IPacketHandler.h"

namespace PacketHandler {
	class Login : public IPacketHandler
	{
	public:
		bool RequireLogin() override { return false; };

		bool Validate(ClientSessionRef& session, BYTE* buffer, int32 len) override;

		void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len) override;
	};
}

