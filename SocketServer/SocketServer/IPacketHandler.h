#pragma once

class IPacketHandler {
public:
	virtual bool RequireLogin() { return true; };
	virtual void HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len) abstract;
	virtual bool Validate(ClientSessionRef& session, BYTE* buffer, int32 len) abstract;
};