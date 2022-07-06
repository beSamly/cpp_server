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

	// �ش� �̸��Ͽ� ������ ���� ��
	if (account == nullptr) {
		HandleFail(session, "AccountId does not exist");
		return;
	}

	// ��й�ȣ�� Ʋ�� ��
	if (wstring(password.begin(), password.end()) != account->GetPassword()) {
		HandleFail(session, "Invalid authentication info");
	}

	auto accountId = account->GetAccountId();
	PlayerRef player = MakeShared<Player>(accountId);

	// DB�� ���� ���� ���� �о����
	player->LoadPlayerFromDB();

	// ��Ʈ��ũ ���ǰ� ����
	session->SetPlayer(player);

	GPlayerManager->AddPlayer(player);

	// Response ������
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