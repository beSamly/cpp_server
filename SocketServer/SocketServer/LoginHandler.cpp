#include "pch.h"
#include "LoginHandler.h"
#include "LoginRequest.pb.h"
#include <PacketHeader.h>

void LoginHandler::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Log->Info("[LoginRequest Packet] info email : " + pkt.email() + " password : " + pkt.password());
}
