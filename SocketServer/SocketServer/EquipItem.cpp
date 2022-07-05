#include "pch.h"
#include "EquipItem.h"
#include "ColumnDataType.h"
#include "Column.h"

EquipItem::EquipItem(int32 accountId, int32 slotIndex, int32 equipItemIndex, int32 star)
{
	SetAccountId(accountId);
	SetSlotIndex(slotIndex);
	SetEquipItemIndex(equipItemIndex);
	SetStar(star);
}
