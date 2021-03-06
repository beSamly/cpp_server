#include "pch.h"
#include "PacketManager.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "Login.h"
#include "BuyEquipItem.h"
#include "BreakEquipItem.h"
#include "UpgradeEquipItem.h"

PacketManager::PacketManager()
{
	Init();
}

PacketManager::~PacketManager()
{
}

void PacketManager::Init() {
	_handlers = Vector<IPacketHandler*>(UINT16_MAX, nullptr);
	_handlers[PacketId::LOGIN_REQ] = dynamic_cast<IPacketHandler*>(new PacketHandler::Login());
	_handlers[PacketId::BUY_EQUIP_ITEM] = dynamic_cast<IPacketHandler*>(new PacketHandler::BuyEquipItem());
	_handlers[PacketId::BREAK_EQUIP_ITEM] = dynamic_cast<IPacketHandler*>(new PacketHandler::BreakEquipItem());
	_handlers[PacketId::UPGRADE_EQUIP_ITEM] = dynamic_cast<IPacketHandler*>(new PacketHandler::UpgradeEquipItem());
}

void PacketManager::HandlePacket(ClientSessionRef& session, int16 packetId, BYTE* buffer, int32 len) {

	IPacketHandler* packetHandler = _handlers[packetId];

	if (packetHandler == nullptr) {
		Log->Debug("[PacketManager] invalid packetId = " + packetId);
		return;
	}

	bool requireLogin = packetHandler->RequireLogin();
	if (requireLogin && session->GetPlayer() == nullptr) {
		Log->Debug(format("[PacketManager] invalid packetId = {}", packetId));
		return;
	}

	if (!packetHandler->Validate(session, buffer, len)) {
		Log->Debug(format("[PacketManager] validation failed for packetId = {}", packetId));
		return;
	}

	_handlers[packetId]->HandlePacket(session, buffer, len);
}