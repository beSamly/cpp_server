#pragma once
#include "DBConnectionPool.h"
#include "DBConnection.h"

template<typename T>
class DBModel
{
public:
	/* 인터페이스 */
	virtual ColumnInfoVector GetPrimaryKeyInfo() abstract;
	virtual ColumnInfoVector GetUpdateInfo() abstract;

public:
	static CollectionRef<T> FindAll(int32 accountId) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
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
			case ColumnDataType::int32:
				dbConnection->BindCol(count, static_pointer_cast<int32>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			case ColumnDataType::TIMESTAMP_STRUCT:
				dbConnection->BindCol(count, static_pointer_cast<TIMESTAMP_STRUCT>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			}
			count++;
		}

		columnNames = columnNames.substr(0, columnNames.size() - 1);
		String query = (prefix + columnNames + L" FROM [dbo].[" + tableName + L"]" + L" WHERE AccountId = (?)");

		/*-------------------------
		|	Binding Parameter     |
		--------------------------*/
		SQLLEN accountLen = 0;
		dbConnection->BindParam(1, &accountId, &accountLen);

		/*---------------------------------
		|	Execute query and fetch data  |
		----------------------------------*/
		auto collection = MakeShared<Collection<T>>();
		if (!dbConnection->Execute(query.c_str())) {
			return collection;
			//return nullptr;
		}

		while (dbConnection->Fetch())
		{
			T data(columnInfo);
			collection->Add(data.GetUniqueKey(), data, false);
		}

		return collection;
	};

	bool Save() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();

		ColumnInfoVector updateInfo = GetUpdateInfo();

		String prefix = L"INSERT INTO ";
		String tableName = T::GetTableName();

		//DBBind<3, 0> dbBind(*dbConn, L"INSERT INTO [dbo].[Gold]([gold], [name], [createDate]) VALUES(?, ?, ?)");

		String columnNames;
		String valuesString;

		int32 count = 1;
		SQLLEN sqllen = 0;

		for (const ColumnInfo& columnInfo : updateInfo._vector)
		{
			auto columnName = columnInfo._columnName;
			auto dataType = columnInfo._dataType;

			columnNames += (columnName + L",");
			valuesString += L"?,";

			switch (dataType) {
			case ColumnDataType::int32:
				dbConnection->BindParam(count, static_pointer_cast<int32>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			case ColumnDataType::TIMESTAMP_STRUCT:
				dbConnection->BindParam(count, static_pointer_cast<TIMESTAMP_STRUCT>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			}
			count++;
		}

		columnNames = columnNames.substr(0, columnNames.size() - 1);
		valuesString = valuesString.substr(0, valuesString.size() - 1);


		auto query = std::format(L"INSERT INTO [dbo].[{}]({}) VALUES({})", tableName, columnNames, valuesString);
		if (!dbConnection->Execute(query.c_str())) {
			return false;
			//return nullptr;
		}

		return true;
	}

	bool Remove() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();

		dbConnection->Unbind();

		ColumnInfoVector keyInfo = GetPrimaryKeyInfo();

		String tableName = T::GetTableName();

		String condition;

		int32 count = 1;
		SQLLEN sqllen = 0;

		for (const ColumnInfo& columnInfo : keyInfo._vector)
		{
			auto columnName = columnInfo._columnName;
			auto dataType = columnInfo._dataType;

			condition += (columnName + L"=(?) AND ");

			switch (dataType) {
			case ColumnDataType::int32:
				dbConnection->BindParam(count, static_pointer_cast<int32>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			case ColumnDataType::TIMESTAMP_STRUCT:
				dbConnection->BindParam(count, static_pointer_cast<TIMESTAMP_STRUCT>(columnInfo._columnValuePtr).get(), &sqllen);
				break;
			}
			count++;
		}

		condition = condition.substr(0, condition.size() - 4);


		auto query = std::format(L"DELETE FROM [dbo].[{}] WHERE {}", tableName, condition);
		if (!dbConnection->Execute(query.c_str())) {
			return false;
			//return nullptr;
		}

		return true;
	}

	void Update() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		return;
	}


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
};

