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
	int32				_star;
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
	/* Getter Setter */
	int32 GetStar() { DBModel::MarkAsUpdated(); return _star; };
	void SetStar(int32 star) { _star = star; };

public:
	/* 인터페이스 구현 */
	ColumnInfoVector	GetUpdateInfo();
	ColumnInfoVector	GetPrimaryKeyInfo();
	int32				GetUniqueKey();

	/* Static methods */
	static ColumnInfoVector GetColumnInfo();
	static String GetTableName();
};

