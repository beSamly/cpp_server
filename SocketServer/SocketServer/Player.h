#pragma once
#include "Collection.h"
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
	void LoadPlayerFromDB(DBConnection* connection);
};

