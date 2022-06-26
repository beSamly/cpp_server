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
	CollectionRef<EquipItem> equipItemCollection;
public:
	int32 GetAccountId();
	void LoadPlayerFromDB(DBConnection* connection);

public:
	EquipItem AddEquipItem(int32 equipItemIndex);
	EquipItem RemoveEquipItem(int32 slotIndex);
};

