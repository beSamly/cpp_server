#include "pch.h"
#include "PacketHandlerManager.h"

bool Handle_INVALID(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}