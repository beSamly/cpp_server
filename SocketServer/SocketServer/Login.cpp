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
#include "LoginResponse.pb.h"

bool PacketHandler::Login::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return false;

	if (!InputValidator::IsEmail(pkt.email())) {
		HandleFail(session, "Invalid Email form");
		return false;
	};

	if (!InputValidator::IsValidPassword(pkt.password())) {
		HandleFail(session, "Invalid authentication info");
		return false;
	};

	return true;
}

void PacketHandler::Login::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginRequest pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto email = pkt.email();
	auto password = pkt.password();
	auto w_email = wstring(email.begin(), email.end());

	auto account = Account().FindOneByEmail(w_email);

	// 해당 이메일에 계정이 없을 때
	if (account == nullptr) {
		HandleFail(session, "AccountId does not exist");
		return;
	}

	// 비밀번호가 틀릴 때
	if (wstring(password.begin(), password.end()) != account->GetPassword()) {
		HandleFail(session, "Invalid authentication info");
	}

	auto accountId = account->GetAccountId();
	PlayerRef player = MakeShared<Player>(accountId);

	// DB로 부터 유저 정보 읽어오기
	player->LoadPlayerFromDB();

	// 네트워크 세션과 연동
	session->SetPlayer(player);

	GPlayerManager->AddPlayer(player);

	// Response 보내기
	Protocol::LoginResponse response;
	response.set_result(true);

	Vector<EquipItemRef> equipItems = player->GetEquipItems();
	for (EquipItemRef source : equipItems) {
		source->CopyToProtobuf(response.add_equipitems());
	}

	session->SendLoginResponse(response);
}

void PacketHandler::Login::HandleFail(ClientSessionRef& session, string reason) {
	Protocol::LoginResponse response;
	response.set_result(false);
	response.set_message(reason);
	session->SendLoginResponse(response);
	return;
}