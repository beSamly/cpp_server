#include "pch.h"
#include "BuyEquipItem.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "PacketHeader.h"
#include "BuyEquipItem.pb.h"
#include "ClientSession.h"

void PacketHandler::BuyEquipItem::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{

	Protocol::BuyEquipItem pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto equipItemIndex = pkt.equipitemindex();
	auto player = session->GetPlayer();
	EquipItem equipItem = player->AddEquipItem(equipItemIndex);
}
