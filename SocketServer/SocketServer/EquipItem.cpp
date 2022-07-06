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

void EquipItem::CopyToProtobuf(Protocol::EquipItem* equipItem)
{
	equipItem->set_equipitemindex(this->GetEquipItemIndex());
	equipItem->set_slotindex(this->GetSlotIndex());
	equipItem->set_star(this->GetStar());
}
