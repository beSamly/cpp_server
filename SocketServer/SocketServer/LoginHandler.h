#pragma once
#include "IPacketHandler.h"

class LoginHandler : public IPacketHandler
{
public:
	void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len);
};

