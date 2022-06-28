#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"

class EquipItem : public DBModel<EquipItem>
{
private:
	int32				_accountId;
	int32				_slotIndex;
	int32				_equipItemIndex;
	TIMESTAMP_STRUCT	_createdAt;

public:
	EquipItem(ColumnInfoVector& columnInfo);
	EquipItem(int32 accountId, int32 slotIndx, int32 equipItemIndex) : _accountId(accountId), _slotIndex(slotIndx), _equipItemIndex(equipItemIndex) {
		// TImeStampHelper 생성
		TIMESTAMP_STRUCT now;
		now.fraction = 0;
		now.hour = 0;
		now.minute = 0;
		now.second = 0;
		now.year = 2022;
		now.month = 11;
		now.day = 13;
		_createdAt = now;
	};
	EquipItem() = default;

public:
	/* 인터페이스 구현 */
	ColumnInfoVector	GetPrimaryKeyInfo();
	ColumnInfoVector	GetUpdateInfo();
	int32				GetUniqueKey();

	/* Static methods */
	static ColumnInfoVector GetColumnInfo();
	static String GetTableName();
};

