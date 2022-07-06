#include "pch.h"
#include "UpgradeEquipItem.h"
#include "PacketHeader.h"
#include "EquipItem.h"
#include "Player.h"
#include "UpgradeEquipItem.pb.h"

bool PacketHandler::UpgradeEquipItem::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	// TODO Input validation
	return true;
}

void PacketHandler::UpgradeEquipItem::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::UpgradeEquipItem pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto slotIndex = pkt.slotindex();
	auto player = session->GetPlayer();

	// SlotIndex에 해당하는 장비 찾기
	EquipItemRef equipItem = player->GetEquipItem(slotIndex);
	if (equipItem == nullptr) {
		Log->Error(format("[UpgradeEquipItem] Player do not have equipItem with SlotIndex = {}, AccountId={}", slotIndex, player->GetAccountId()));
		return;
	}

	// 성 업그레이드
	int32 newStar = equipItem->GetStar() + 1;
	equipItem->SetStar(newStar);
}
