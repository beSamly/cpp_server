#pragma once

class IPacketHandler {
public:
	virtual bool RequireLogin() { return true; };
	virtual void HandlePacket(ServerSessionRef& session, BYTE* buffer, int32 len) abstract;
	virtual bool Validate(ServerSessionRef& session, BYTE* buffer, int32 len) abstract;
};