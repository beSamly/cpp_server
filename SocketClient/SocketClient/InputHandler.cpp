#include "pch.h"
#include "InputHandler.h"
#include "Logger.h"
#include "LoginRequest.pb.h"
#include "PacketManager.h"
#include "PacketId.h"
#include "BuyEquipItem.pb.h"
#include "BreakEquipItem.pb.h"
#include "UpgradeEquipItem.pb.h"

using std::cin;

void SendLoginRequest(SocketClientRef socketClient);
void SendBuyEquipItem(SocketClientRef socketClient);
void SendBreakEquipItem(SocketClientRef socketClient);
void SendUpgradeEquipItem(SocketClientRef socketClient);

void InputHandler::Init()
{
	_inputHandlers[1] = SendLoginRequest;
	_inputHandlers[2] = SendBuyEquipItem;
	_inputHandlers[3] = SendBreakEquipItem;
	_inputHandlers[4] = SendUpgradeEquipItem;
}

void InputHandler::HandleInput(SocketClientRef socketClient, int32 key)
{
	if (_inputHandlers[key]) {
		_inputHandlers[key](socketClient);
	}
}

void SendLoginRequest(SocketClientRef socketClient) {
	string email;
	string password;

	cout << "email : " << endl;
	cin >> email;

	cout << "password : " << endl;
	cin >> password;

	Protocol::LoginRequest pkt;
	pkt.set_email(email);
	pkt.set_password(password);

	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::LOGIN_REQ);
	socketClient->_serverSession->Send(buffer);
}

void SendBuyEquipItem(SocketClientRef socketClient) {
	int32 equipItemIndex;

	cout << "EquipItemIndex : " << endl;
	cin >> equipItemIndex;


	Protocol::BuyEquipItem pkt;
	pkt.set_equipitemindex(equipItemIndex);
	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::BUY_EQUIP_ITEM);
	socketClient->_serverSession->Send(buffer);
}

void SendBreakEquipItem(SocketClientRef socketClient) {
	int32 slotIndex;

	cout << "SlotIndex : " << endl;
	cin >> slotIndex;

	Protocol::BreakEquipItem pkt;
	pkt.set_slotindex(slotIndex);
	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::BREAK_EQUIP_ITEM);
	socketClient->_serverSession->Send(buffer);
}

void SendUpgradeEquipItem(SocketClientRef socketClient) {
	int32 slotIndex;

	cout << "SlotIndex : " << endl;
	cin >> slotIndex;

	Protocol::UpgradeEquipItem pkt;
	pkt.set_slotindex(slotIndex);
	SendBufferRef buffer = PacketManager::PacketToSendBuffer(pkt, PacketId::UPGRADE_EQUIP_ITEM);
	socketClient->_serverSession->Send(buffer);
}

