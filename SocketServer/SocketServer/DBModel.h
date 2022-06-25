#pragma once
#include "DBConnection.h"
#include "ColumnInfo.h"
#include "Collection.h"

template<typename T>
class DBModel
{
public:
	/* 인터페이스 */
	virtual ColumnInfoVector GetPrimaryKeyInfo() abstract;
	virtual ColumnInfoVector GetUpdateInfo() abstract;

public:
	//static MapRef<int32, T> FindAll(DBConnection* dbConnection, int32 accountId) {
	static CollectionRef<T> FindAll(DBConnection* dbConnection, int32 accountId) {
		dbConnection->Unbind();

		ColumnInfoVector columnInfo = T::GetColumnInfo();

		String prefix = L"SELECT ";
		String tableName = T::GetTableName();
		String columnNames;


		int32 count = 1;
		SQLLEN sqllen = 0;


		for (const ColumnInfo& columnInfo : columnInfo._vector)
		{
			auto columnName = columnInfo._columnName;
			auto dataType = columnInfo._dataType;

			columnNames += (columnName + L",");

			switch (dataType) {
			case ColumnDataType::int32: {
				dbConnection->BindCol(count, static_pointer_cast<int32>(columnInfo._columnValuePtr).get(), &sqllen);
			}
			break;

			case ColumnDataType::TIMESTAMP_STRUCT:
			{
				dbConnection->BindCol(count, static_pointer_cast<TIMESTAMP_STRUCT>(columnInfo._columnValuePtr).get(), &sqllen);
			}
			break;
			}
			count++;
		}

		columnNames = columnNames.substr(0, columnNames.size() - 1);
		String fullQuery = (prefix + columnNames + L" FROM [dbo].[" + tableName + L"]" + L" WHERE AccountId = (?)");

		//int32 slotIndex;
		//int32 equipItemIndex;
		//int32 accountIdOut;
		//TIMESTAMP_STRUCT createdAt;
		//SQLLEN sqllen1 = 0;
		//SQLLEN sqllen2 = 0;
		//SQLLEN sqllen3 = 0;
		//SQLLEN sqllen4 = 0;

		//dbConnection->BindCol(1, &slotIndex, &sqllen1);
		//dbConnection->BindCol(2, &equipItemIndex, &sqllen2);
		//dbConnection->BindCol(3, &createdAt, &sqllen3);

		SQLLEN accountLen = 0;
		dbConnection->BindParam(1, &accountId, &accountLen);


		auto collection = MakeShared<Collection<T>>();

		if (!dbConnection->Execute(fullQuery.c_str())) {
			return collection;
			//return nullptr;
		}

		while (dbConnection->Fetch())
		{
			T data(columnInfo);
			collection->Add(data.GetUniqueKey(), data);
		}
		
		return collection;
	}

	/*public void Save() {

	};

	public void Delete() {

	}*/

	/*MapRef<int32, T> FindAllArch(DBConnection* dbConnection, int32 accountId) {
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
	}*/

	//static String GetSelectQuery() virtual;
};

