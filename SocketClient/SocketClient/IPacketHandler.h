#pragma once

class IPacketHandler {
public:
	virtual void HandlePacket(ServerSessionRef& session, BYTE* buffer, int32 len) abstract;
};