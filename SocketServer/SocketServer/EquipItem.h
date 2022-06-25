#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"

class EquipItem : public DBModel<EquipItem>
{
public:
	/* Static methods */
	static ColumnInfoVector GetColumnInfo() {
		ColumnInfoVector infoVector;
		infoVector.AddColumnInfo(L"AccountId", ColumnDataType::int32, MakeShared<int32>());
		infoVector.AddColumnInfo(L"SlotIndex", ColumnDataType::int32, MakeShared<int32>());
		infoVector.AddColumnInfo(L"EquipItemIndex", ColumnDataType::int32, MakeShared<int32>());
		infoVector.AddColumnInfo(L"CreatedAt", ColumnDataType::TIMESTAMP_STRUCT, MakeShared<TIMESTAMP_STRUCT>());
		return infoVector;
	}

	static String GetTableName() { return L"EquipItem"; }
public:
	int32 _accountId;
	int32 _slotIndex;
	int32 _equipItemIndex;
	TIMESTAMP_STRUCT _createdAt;

public:
	EquipItem(ColumnInfoVector& columnInfo);
	EquipItem() = default;

public:
	/* 인터페이스 구현 */
	ColumnInfoVector GetPrimaryKeyInfo();
	ColumnInfoVector GetUpdateInfo();
	int32 GetUniqueKey();
};

