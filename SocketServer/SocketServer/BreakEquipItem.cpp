#include "pch.h"
#include "BreakEquipItem.h"
#include "Player.h"
#include "DBConnectionPool.h"
#include "PacketHeader.h"
#include "BreakEquipItem.pb.h"
#include "ClientSession.h"

void PacketHandler::BreakEquipItem::HandlePacket(ClientSessionRef& session, BYTE* buffer, int32 len)
{

	Protocol::BreakEquipItem pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	auto slotIndex = pkt.slotindex();
	auto player = session->GetPlayer();
	player->RemoveEquipItem(slotIndex);
}

bool PacketHandler::BreakEquipItem::Validate(ClientSessionRef& session, BYTE* buffer, int32 len)
{
	// TODO Input validation
	return true;
}

