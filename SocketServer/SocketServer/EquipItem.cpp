#include "pch.h"
#include "EquipItem.h"
#include "DBConnection.h"

MapRef<int32, EquipItem> EquipItem::FindAll(DBConnection* dbConnection, int32 accountId)
{
	dbConnection->Unbind();
	auto query = L"SELECT SlotIndex, EquipItemIndex, CreatedAt FROM [dbo].[EquipItem] WHERE AccountId = (?)";

	int32 slotIndex;
	int32 equipItemIndex;
	int32 accountIdOut;
	TIMESTAMP_STRUCT createdAt;
	SQLLEN sqllen1 = 0;
	SQLLEN sqllen2 = 0;
	SQLLEN sqllen3 = 0;
	SQLLEN sqllen4 = 0;
	
	dbConnection->BindCol(1, &slotIndex, &sqllen1);
	dbConnection->BindCol(2, &equipItemIndex, &sqllen2);
	dbConnection->BindCol(3, &createdAt, &sqllen3);

	dbConnection->BindParam(1, &accountId, &sqllen4);

	if (!dbConnection->Execute(query)) {
		return nullptr;
	}

	auto mapRef = MakeShared<Map<int32, EquipItem>>();

	while (dbConnection->Fetch())
	{
		EquipItem equipItem;
		equipItem._slotIndex = slotIndex;
		equipItem._equipItemIndex = equipItemIndex;
		equipItem._createdAt = createdAt;

		mapRef->insert(std::make_pair(equipItem._slotIndex, equipItem));
	}

	return mapRef;
}
