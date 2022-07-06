#include "pch.h"
#include "LoginResponse.h"
#include "PacketHeader.h"
#include "LoginResponse.pb.h"
#include "Logger.h"

bool PacketHandler::LoginResponse::Validate(ServerSessionRef& session, BYTE* buffer, int32 len)
{
	return true;
}

void PacketHandler::LoginResponse::HandlePacket(ServerSessionRef& session, BYTE* buffer, int32 len)
{
	Protocol::LoginResponse pkt;
	if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	if (!pkt.result()) {
		Log->Error(format("Login failed message = {}", pkt.message()));
		return;
	}

	Log->Info(format("Login successful"));
	for (auto& equipItem : pkt.equipitems())
	{
		Log->Info(format("EquipItemIndex = {} SlotIndex = {} Star = {}", equipItem.equipitemindex(), equipItem.slotindex(), equipItem.star()));
	}
}

