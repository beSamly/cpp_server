#pragma once

class IPacketHandler {
public:
	virtual void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len) abstract;
};