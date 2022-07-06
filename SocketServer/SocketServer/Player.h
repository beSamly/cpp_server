#pragma once
#include "EquipItem.h"
#include "DBConnection.h"

class Player
{
public:
	Player(int32 accountId) : _accountId(accountId) {};
	~Player();
private:
	int32 _accountId;
public:
	CollectionRef<EquipItemRef> equipItemCollection;
public:
	int32 GetAccountId();
	void LoadPlayerFromDB();
	void Update();

public:
	EquipItemRef AddEquipItem(int32 equipItemIndex);
	EquipItemRef GetEquipItem(int32 slotIndex);
	Vector<EquipItemRef> GetEquipItems();

	bool RemoveEquipItem(int32 slotIndex);
};

