#include "pch.h"
#include "EquipItem.h"
#include "ColumnDataType.h"
#include "ColumnInfo.h"
namespace {
	String ACCOUNT_ID = L"AccountId";
	String SLOT_INDEX = L"SlotIndex";
	String EQUIP_ITEM_INDEX = L"EquipItemIndex";
	String CREATED_AT = L"CreatedAt";
	String EQUIP_ITEM_TABLE_NAME = L"EquipItem";
	String STAR = L"Star";
}

ColumnInfoVector EquipItem::GetColumnInfo() {
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ACCOUNT_ID, ColumnDataType::INT32);
	infoVector.AddColumnInfo(SLOT_INDEX, ColumnDataType::INT32);
	infoVector.AddColumnInfo(EQUIP_ITEM_INDEX, ColumnDataType::INT32);
	infoVector.AddColumnInfo(STAR, ColumnDataType::INT32);
	infoVector.AddColumnInfo(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT);
	return infoVector;
};

String EquipItem::GetTableName() { return EQUIP_ITEM_TABLE_NAME; };

EquipItem::EquipItem(ColumnInfoVector& columnInfo)
{
	_accountId = columnInfo.FindValueByColumnName<int32>(ACCOUNT_ID);
	_equipItemIndex = columnInfo.FindValueByColumnName<int32>(EQUIP_ITEM_INDEX);
	_slotIndex = columnInfo.FindValueByColumnName<int32>(SLOT_INDEX);
	_star = columnInfo.FindValueByColumnName<int32>(STAR);
	_createdAt = columnInfo.FindValueByColumnName<TIMESTAMP_STRUCT>(CREATED_AT);
};

ColumnInfoVector EquipItem::GetPrimaryKeyInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ACCOUNT_ID, _accountId);
	infoVector.AddColumnInfo(SLOT_INDEX, _slotIndex);
	return infoVector;
};

ColumnInfoVector EquipItem::GetUpdateInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ACCOUNT_ID, _accountId);
	infoVector.AddColumnInfo(SLOT_INDEX, _slotIndex);
	infoVector.AddColumnInfo(EQUIP_ITEM_INDEX, _equipItemIndex);
	infoVector.AddColumnInfo(STAR, _star);
	infoVector.AddColumnInfo(CREATED_AT, _createdAt);
	return infoVector;
};

int32 EquipItem::GetUniqueKey() {
	return _slotIndex;
};


