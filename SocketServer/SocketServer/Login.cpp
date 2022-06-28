#include "pch.h"
#include "Login.h"
#include "LoginRequest.pb.h"
#include "PacketHeader.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "Login.h"
#include "PlayerManager.h"

void PacketHandler::Login::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Log->Info("[LoginRequest Packet] info email : " + pkt.email() + " password : " + pkt.password());

	// TODO find account from db
	// TODO load player
	PlayerRef player = MakeShared<Player>(1);
	player->LoadPlayerFromDB();

	// TODO add player to clientSession
	session->SetPlayer(player);

	GPlayerManager->AddPlayer(player);
}



	
