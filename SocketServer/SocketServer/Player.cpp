#include "pch.h"
#include "Player.h"
#include "EquipItem.h"

int32 Player::GetAccountId()
{
	return _accountId;
}

void Player::LoadPlayerFromDB(){
	equipItemCollection = EquipItem::FindAll(_accountId);
	//equipItemCollection.SetData(EquipItem::FindAll(connection, _accountId));
}
void Player::Update()
{
	equipItemCollection->Update();
}

EquipItem Player::AddEquipItem(int32 equipItemIndex)
{
	int32 slotIndex = 14;
	EquipItem newItem(_accountId, slotIndex, equipItemIndex);
	equipItemCollection->Add(slotIndex, newItem);
	return newItem;
}

bool Player::RemoveEquipItem(int32 slotIndex)
{
	equipItemCollection->Remove(slotIndex);
	return true;
}
;

Player::~Player(){}

