#include "pch.h"
#include "Player.h"
#include "Collection.h"
#include "EquipItem.h"

void Player::LoadPlayerFromDB(DBConnection* connection){
	equipItemCollection.SetData(EquipItem::FindAll(connection, _accountId));
};

Player::~Player(){}

