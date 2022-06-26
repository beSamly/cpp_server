#include "pch.h"
#include "Player.h"
#include "EquipItem.h"

int32 Player::GetAccountId()
{
	return _accountId;
}

void Player::LoadPlayerFromDB(DBConnection* connection){
	equipItemCollection = EquipItem::FindAll(connection, _accountId);
	//equipItemCollection.SetData(EquipItem::FindAll(connection, _accountId));
}
EquipItem Player::AddEquipItem(int32 equipItemIndex)
{
	int32 slotIndex = 14;
	EquipItem newItem(_accountId, slotIndex, equipItemIndex);
	equipItemCollection->Add(slotIndex, newItem);
	return newItem;
}
EquipItem Player::RemoveEquipItem(int32 slotIndex)
{
	return equipItemCollection->Remove(slotIndex);
}
;

Player::~Player(){}

