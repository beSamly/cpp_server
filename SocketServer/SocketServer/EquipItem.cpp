#include "pch.h"
#include "EquipItem.h"
#include "ColumnDataType.h"
#include "ColumnInfo.h"

EquipItem::EquipItem(ColumnInfoVector& columnInfo)
{
	_accountId = columnInfo.FindValueByColumnName<int32>(L"AccountId");
	_equipItemIndex = columnInfo.FindValueByColumnName<int32>(L"EquipItemIndex");
	_slotIndex = columnInfo.FindValueByColumnName<int32>(L"SlotIndex");
	_createdAt = columnInfo.FindValueByColumnName<TIMESTAMP_STRUCT>(L"CreatedAt");
}

ColumnInfoVector EquipItem::GetPrimaryKeyInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(L"AccountId", ColumnDataType::int32, static_pointer_cast<void>(MakeShared<int32>(_accountId)));
	return infoVector;
}

ColumnInfoVector EquipItem::GetUpdateInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(L"SlotIndex", ColumnDataType::int32, static_pointer_cast<void>(MakeShared<int32>(_slotIndex)));
	infoVector.AddColumnInfo(L"EquipItemIndex", ColumnDataType::int32, static_pointer_cast<void>(MakeShared<int32>(_equipItemIndex)));
	infoVector.AddColumnInfo(L"CreatedAt", ColumnDataType::TIMESTAMP_STRUCT, static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>(_createdAt)));
	return infoVector;
}

int32 EquipItem::GetUniqueKey() {
	return _slotIndex;
}


