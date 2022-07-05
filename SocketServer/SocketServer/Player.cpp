#include "pch.h"
#include "Player.h"
#include "EquipItem.h"

int32 Player::GetAccountId()
{
	return _accountId;
}

void Player::LoadPlayerFromDB() {
	equipItemCollection = EquipItem().FindAllByAccountId(_accountId);
}

void Player::Update()
{
	equipItemCollection->Update();
}

EquipItemRef Player::AddEquipItem(int32 equipItemIndex)
{
	int32 slotIndex;
	for (int i = 1; i < UINT32_MAX; i++) {
		bool exist = equipItemCollection->KeyExist(i);
		if (!exist) {
			slotIndex = i;
			break;
		}
	}

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

Player::~Player() {}

