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

EquipItemRef Player::AddEquipItem(int32 equipItemIndex)
{
	int32 slotIndex = 14;
	auto newItem = MakeShared<EquipItem>(_accountId, slotIndex, equipItemIndex);
	equipItemCollection->Add(slotIndex, newItem);
	return newItem;
}

EquipItemRef Player::GetEquipItem(int32 slotIndex)
{
	return equipItemCollection->Find(slotIndex);
}

bool Player::RemoveEquipItem(int32 slotIndex)
{
	equipItemCollection->Remove(slotIndex);
	return true;
}
;

Player::~Player(){}

