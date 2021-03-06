#include "pch.h"
#include "BuyEquipItem.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "PacketHeader.h"
#include "BuyEquipItem.pb.h"
#include "ClientSession.h"

bool PacketHandler::BuyEquipItem::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	// TODO Input validation - 구매할 수 있는 조건이 되는지 등등
	return true;
}


void PacketHandler::BuyEquipItem::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::BuyEquipItem pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto equipItemIndex = pkt.equipitemindex();
	auto player = session->GetPlayer();
	EquipItemRef equipItem = player->AddEquipItem(equipItemIndex);
}
