#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"

class EquipItem : public DBModel<EquipItem>
{
public:
	int32				_accountId;
	int32				_slotIndex;
	int32				_equipItemIndex;
	TIMESTAMP_STRUCT	_createdAt;

public:
	EquipItem(ColumnInfoVector& columnInfo);
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

