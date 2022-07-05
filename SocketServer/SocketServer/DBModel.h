#pragma once
#include "DBConnectionPool.h"
#include "DBConnection.h"
#include "DBQueryHelper.h"
#include "TableInfo.h"

template<typename T>
class DBModel
{
protected:


public:
	/* 인터페이스 */
	virtual String GetTableName() abstract;
	virtual TableInfo* GetTableInfo() abstract;

public:
	CollectionRef<shared_ptr<T>> FindAllByAccountId(int32 accountId) {
		ColumnInfoVector primaryKeyInfo;
		primaryKeyInfo.AddColumnInfo(ColumnInfo(L"AccountId", accountId));
		return FindAll(primaryKeyInfo);
	}

	shared_ptr<T> FindOne(ColumnInfoVector primaryKeyInfo) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		TableInfo* tableInfo = GetTableInfo();

		ColumnInfoVector columnInfo = tableInfo->GetColumnInfo();
		SQLLEN sqllen = 0;
		DBQueryHelper::BindCol(&columnInfo, dbConnection, &sqllen);

		/*-------------------------
		|	Binding Parameter     |
		--------------------------*/
		DBQueryHelper::BindParam(&primaryKeyInfo, dbConnection, &sqllen);

		/*---------------------------------
		|	Execute query and fetch data  |
		----------------------------------*/
		Vector<String> columnNames = columnInfo.ExtractKeyNames();
		Vector<String> keyNames = primaryKeyInfo.ExtractKeyNames();
		String query = DBQueryHelper::buildSelectQuery(GetTableName(), columnNames, keyNames);

		if (!dbConnection->Execute(query.c_str())) {
			return nullptr;
		}

		if (dbConnection->Fetch()) {
			auto data = MakeShared<T>();
			data->GetTableInfo()->Mapping(columnInfo);
			return data;
		}
		else {
			return nullptr;
		}
	};

	bool Insert() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();

		TableInfo* tableInfo = GetTableInfo();
		ColumnInfoVector updateInfo = tableInfo->GetInsertInto();

		SQLLEN sqllen = 0;
		DBQueryHelper::BindParam(&updateInfo, dbConnection, &sqllen);

		Vector<String> columnNames = updateInfo.ExtractKeyNames();

		auto query = DBQueryHelper::buildInsertQuery(GetTableName(), columnNames);
		if (!dbConnection->Execute(query.c_str())) {
			return false;
		}

		return true;
	}

	bool Remove() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		SQLLEN sqllen = 0;
		TableInfo* tableInfo = GetTableInfo();

		ColumnInfoVector keyInfo = tableInfo->GetPrimaryKeyInfo();
		DBQueryHelper::BindParam(&keyInfo, dbConnection, &sqllen);

		Vector<String> keyNames = keyInfo.ExtractKeyNames();
		auto query = DBQueryHelper::buildDeleteQuery(GetTableName(), keyNames);
		if (!dbConnection->Execute(query.c_str())) {
			return false;
			//return nullptr;
		}

		return true;
	}

	void Update() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		SQLLEN sqllen = 0;

		TableInfo* tableInfo = GetTableInfo();

		ColumnInfoVector columnInfo = tableInfo->GetUpdateInfo();
		ColumnInfoVector primaryKeyInfo = tableInfo->GetPrimaryKeyInfo();
		Vector<String> columnNames = columnInfo.ExtractKeyNames();
		Vector<String> primaryKeyNames = primaryKeyInfo.ExtractKeyNames();

		columnInfo.Concat(primaryKeyInfo);
		DBQueryHelper::BindParam(&columnInfo, dbConnection, &sqllen);

		auto query = DBQueryHelper::buildUpdateQuery(GetTableName(), columnNames, primaryKeyNames);
		if (!dbConnection->Execute(query.c_str())) {
			return;
		}
	}

	/*------------------------
	|		Version 2		 |
	-------------------------*/
	CollectionRef<shared_ptr<T>> FindAll(ColumnInfoVector primaryKeyInfo) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		TableInfo* tableInfo = GetTableInfo();
		ColumnInfoVector columnInfo = tableInfo->GetColumnInfo();
		SQLLEN sqllen = 0;
		DBQueryHelper::BindCol(&columnInfo, dbConnection, &sqllen);

		/*-------------------------
		|	Binding Parameter     |
		--------------------------*/
		DBQueryHelper::BindParam(&primaryKeyInfo, dbConnection, &sqllen);

		/*---------------------------------
		|	Execute query and fetch data  |
		----------------------------------*/
		Vector<String> columnNames = columnInfo.ExtractKeyNames();
		Vector<String> keyNames = primaryKeyInfo.ExtractKeyNames();
		String query = DBQueryHelper::buildSelectQuery(GetTableName(), columnNames, keyNames);

		auto collection = MakeShared<Collection<shared_ptr<T>>>();
		if (!dbConnection->Execute(query.c_str())) {
			return collection;
		}

		while (dbConnection->Fetch())
		{
			auto data = MakeShared<T>();

			TableInfo* tableInfo = data->GetTableInfo();
			tableInfo->Mapping(columnInfo);

			auto uniqueKey = tableInfo->GetUniqueKey();
			/*	data->GetTableInfo()->SetMarkAsUpdated([collection, uniqueKey]() {
					collection->AddUpdatedIndex(uniqueKey);
				});*/
			collection->Add(uniqueKey, data, false);
		}

		return collection;
	};
};

