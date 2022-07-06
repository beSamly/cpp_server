#include "pch.h"
#include "BreakEquipItem.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "PacketHeader.h"
#include "BreakEquipItem.pb.h"
#include "ClientSession.h"

bool PacketHandler::BreakEquipItem::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	// TODO Input validation - 분해 할 수 없는 아이템인지, 해당 아이템을 보유하고 있는지 등등
	return true;
}

void PacketHandler::BreakEquipItem::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::BreakEquipItem pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto slotIndex = pkt.slotindex();
	auto player = session->GetPlayer();
	player->RemoveEquipItem(slotIndex);
}

