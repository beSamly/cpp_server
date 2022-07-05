#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"
#include "TableInfo.h"

namespace {
	String ACCOUNT_ID = L"AccountId";
	String SLOT_INDEX = L"SlotIndex";
	String EQUIP_ITEM_INDEX = L"EquipItemIndex";
	String CREATED_AT = L"CreatedAt";
	String EQUIP_ITEM_TABLE_NAME = L"EquipItem";
	String STAR = L"Star";
}

class EquipItem : public DBModel<EquipItem>
{
private:
	TableInfo _info{
		ColumnInfo(ACCOUNT_ID, ColumnDataType::INT32, Constraint::PRIMARY_KEY),
		ColumnInfo(SLOT_INDEX, ColumnDataType::INT32, Constraint::UNIQUE_KEY),
		ColumnInfo(EQUIP_ITEM_INDEX, ColumnDataType::INT32),
		ColumnInfo(STAR, ColumnDataType::INT32),
		ColumnInfo(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT, Constraint::AUTO_GENERATED)
	};

public:
	/* Getter */
	int32					GetStar() { return _info.Get<int32>(STAR); };
	int32					GetSlotIndex() { return _info.Get<int32>(SLOT_INDEX); };
	int32					GetEquipItemIndex() { return _info.Get<int32>(EQUIP_ITEM_INDEX); };
	TIMESTAMP_STRUCT		GetCreatedAt() { return _info.Get<TIMESTAMP_STRUCT>(CREATED_AT); };

	/* Setter */
	void					SetAccountId(int32 value) { _info.Set<int32>(ACCOUNT_ID, value); };
	void					SetSlotIndex(int32 value) { _info.Set<int32>(SLOT_INDEX, value); };
	void					SetEquipItemIndex(int32 value) { _info.Set<int32>(EQUIP_ITEM_INDEX, value); };
	void					SetStar(int32 value) { _info.Set<int32>(STAR, value); };

public:
	EquipItem(int32 accountId, int32 slotIndex, int32 equipItemIndex, int32 star = 0);
	EquipItem() = default;

public:
	/* 인터페이스 구현 */
	TableInfo* GetTableInfo() { return &_info; };
	String GetTableName() { return EQUIP_ITEM_TABLE_NAME; };
};

