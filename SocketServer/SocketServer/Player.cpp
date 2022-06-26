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
};

Player::~Player(){}

