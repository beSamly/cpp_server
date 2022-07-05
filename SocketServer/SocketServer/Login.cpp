#include "pch.h"
#include "Login.h"
#include "LoginRequest.pb.h"
#include "PacketHeader.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "Login.h"
#include "PlayerManager.h"
#include "InputValidator.h"
#include "Account.h"

bool PacketHandler::Login::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	if (!InputValidator::IsEmail(pkt.email())) {
		return false;
	};

	if (!InputValidator::IsValidPassword(pkt.password())) {
		return false;
	};

	return true;
}

void PacketHandler::Login::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	Log->Info("[LoginRequest Packet] info email : " + pkt.email() + " password : " + pkt.password());

	auto email = pkt.email();
	auto password = pkt.password();
	auto account = Account().FindOneByEmail(wstring(email.begin(), email.end()));
	if (account == nullptr) {
		return;
	}

	if (wstring(password.begin(), password.end()) != account->GetPassword()) {
		return;
	}

	// TODO find account from db
	// TODO load player
	PlayerRef player = MakeShared<Player>(account->GetAccountId());
	player->LoadPlayerFromDB();

	// TODO add player to clientSession
	session->SetPlayer(player);

	GPlayerManager->AddPlayer(player);
}
