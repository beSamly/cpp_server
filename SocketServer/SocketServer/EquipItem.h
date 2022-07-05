#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "Column.h"
#include "TableSchema.h"

class EquipItem : public DBModel<EquipItem>
{
private:
	String ACCOUNT_ID = L"AccountId";
	String SLOT_INDEX = L"SlotIndex";
	String EQUIP_ITEM_INDEX = L"EquipItemIndex";
	String CREATED_AT = L"CreatedAt";
	String STAR = L"Star";

	String EQUIP_ITEM_TABLE_NAME = L"EquipItem";

	TableSchema _data{
		{
			Column(ACCOUNT_ID, ColumnDataType::INT32, ColumnConstraint::PRIMARY_KEY),
			Column(SLOT_INDEX, ColumnDataType::INT32, ColumnConstraint::UNIQUE_KEY),
			Column(EQUIP_ITEM_INDEX, ColumnDataType::INT32),
			Column(STAR, ColumnDataType::INT32),
			Column(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT, ColumnConstraint::AUTO_GENERATED)
		}
	};

public:
	/* Getter */
	int32					GetStar() { return _data.GetColumnValue<int32>(STAR); };
	int32					GetSlotIndex() { return _data.GetColumnValue<int32>(SLOT_INDEX); };
	int32					GetEquipItemIndex() { return _data.GetColumnValue<int32>(EQUIP_ITEM_INDEX); };
	TIMESTAMP_STRUCT		GetCreatedAt() { return _data.GetColumnValue<TIMESTAMP_STRUCT>(CREATED_AT); };

	/* Setter */
	void					SetAccountId(int32 value) { _data.SetColumnValue<int32>(ACCOUNT_ID, value); };
	void					SetSlotIndex(int32 value) { _data.SetColumnValue<int32>(SLOT_INDEX, value); };
	void					SetEquipItemIndex(int32 value) { _data.SetColumnValue<int32>(EQUIP_ITEM_INDEX, value); };
	void					SetStar(int32 value) { _data.SetColumnValue<int32>(STAR, value); };

public:
	EquipItem(int32 accountId, int32 slotIndex, int32 equipItemIndex, int32 star = 0);
	EquipItem() = default;

public:
	/* 인터페이스 구현 */
	TableSchema* GetTableSchema() { return &_data; };
	String GetTableName() { return EQUIP_ITEM_TABLE_NAME; };
};

