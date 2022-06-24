#pragma once
#include "DBConnection.h"

class EquipItem
{
public:
	//const static String tableName = "EquipItem";

	static MapRef<int32, EquipItem> FindAll(DBConnection* dbConnection, int32 accountId);

	static String GetSelectQuery() {

	};
	static String GetUpdateQuery() {

	};
	static String GetInsertQuery() {

	};

public:
	int32 _slotIndex;
	int32 _equipItemIndex;
	TIMESTAMP_STRUCT _createdAt;
};

