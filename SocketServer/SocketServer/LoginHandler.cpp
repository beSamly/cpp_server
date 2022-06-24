#include "pch.h"
#include "LoginHandler.h"
#include "LoginRequest.pb.h"
#include "PacketHeader.h"
#include "Player.h"
#include "DBConnectionPool.h"

void LoginHandler::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Log->Info("[LoginRequest Packet] info email : " + pkt.email() + " password : " + pkt.password());

	// TODO find account from db

	// TODO load player

	// TODO add player to clientSession
	shared_ptr<Player> playerRef = MakeShared<Player>(1);
	auto connection = ConnectionPool->Pop();
	playerRef->LoadPlayerFromDB(connection);
	ConnectionPool->Push(connection);

}
