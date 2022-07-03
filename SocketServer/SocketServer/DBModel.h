#pragma once
#include "DBConnectionPool.h"
#include "DBConnection.h"
#include "DBQueryHelper.h"

template<typename T>
class DBModel
{
protected:
	function<void()>	MarkAsUpdated;
	void SetMarkAsUpdated(function<void()> func) { MarkAsUpdated = func; };

public:
	/* 인터페이스 */
	virtual ColumnInfoVector GetPrimaryKeyInfo() abstract;
	virtual ColumnInfoVector GetUpdateInfo() abstract;

public:

	static CollectionRef<shared_ptr<T>> FindAll(int32 accountId) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		ColumnInfoVector columnInfo = T::GetColumnInfo();
		SQLLEN sqllen = 0;
		DBQueryHelper::BindCol(&columnInfo, dbConnection, &sqllen);

		Vector<String> columnNames = columnInfo.ExtractKeyNames();

		String query = DBQueryHelper::buildSelectQuery(T::GetTableName(), columnNames, accountId);

		/*-------------------------
		|	Binding Parameter     |
		--------------------------*/
		SQLLEN accountLen = 0;
		dbConnection->BindParam(1, &accountId, &accountLen);

		/*---------------------------------
		|	Execute query and fetch data  |
		----------------------------------*/
		auto collection = MakeShared<Collection<shared_ptr<T>>>();
		if (!dbConnection->Execute(query.c_str())) {
			return collection;
		}

		while (dbConnection->Fetch())
		{
			auto data = MakeShared<T>(columnInfo);
			auto uniqueKey = data->GetUniqueKey();
			data->SetMarkAsUpdated([collection, uniqueKey]() {
				collection->AddUpdatedIndex(uniqueKey);
			});
			collection->Add(uniqueKey, data, false);
		}

		return collection;
	};

	static CollectionRef<shared_ptr<T>> FindAllByAccountId(int32 accountId) {
		ColumnInfoVector info;
		info.AddColumnInfo(L"AccountId", accountId);
		return FindAll(info);
	}

	static shared_ptr<T> FindOne(ColumnInfoVector primaryKeyInfo) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		ColumnInfoVector columnInfo = T::GetColumnInfo();
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
		String query = DBQueryHelper::buildSelectQuery(T::GetTableName(), columnNames, keyNames);

		if (!dbConnection->Execute(query.c_str())) {
			return nullptr;
		}

		if (dbConnection->Fetch()) {
			auto data = MakeShared<T>(columnInfo);
			return data;
		}
		else {
			return nullptr;
		}
	};

	static CollectionRef<shared_ptr<T>> FindAll(ColumnInfoVector primaryKeyInfo) {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		dbConnection->Unbind();

		ColumnInfoVector columnInfo = T::GetColumnInfo();
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
		String query = DBQueryHelper::buildSelectQuery(T::GetTableName(), columnNames, keyNames);

		auto collection = MakeShared<Collection<shared_ptr<T>>>();
		if (!dbConnection->Execute(query.c_str())) {
			return collection;
		}

		while (dbConnection->Fetch())
		{
			auto data = MakeShared<T>(columnInfo);
			auto uniqueKey = data->GetUniqueKey();
			data->SetMarkAsUpdated([collection, uniqueKey]() {
				collection->AddUpdatedIndex(uniqueKey);
			});
			collection->Add(uniqueKey, data, false);
		}

		return collection;
	};

	bool Save() {
		DBConnectionGaurdRef dbConnectionGaurd = ConnectionPool->Pop();
		DBConnection* dbConnection = dbConnectionGaurd->GetConnection();
		ColumnInfoVector updateInfo = GetUpdateInfo();

		SQLLEN sqllen = 0;
		DBQueryHelper::BindParam(&updateInfo, dbConnection, &sqllen);

		Vector<String> columnNames = updateInfo.ExtractKeyNames();

		auto query = DBQueryHelper::buildInsertQuery(T::GetTableName(), columnNames);
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

		ColumnInfoVector keyInfo = GetPrimaryKeyInfo();
		DBQueryHelper::BindParam(&keyInfo, dbConnection, &sqllen);

		Vector<String> keyNames = keyInfo.ExtractKeyNames();
		auto query = DBQueryHelper::buildDeleteQuery(T::GetTableName(), keyNames);
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

		ColumnInfoVector columnInfo = GetUpdateInfo();
		ColumnInfoVector primaryKeyInfo = GetPrimaryKeyInfo();
		Vector<String> columnNames = columnInfo.ExtractKeyNames();
		Vector<String> primaryKeyNames = primaryKeyInfo.ExtractKeyNames();

		columnInfo.Concat(primaryKeyInfo);
		DBQueryHelper::BindParam(&columnInfo, dbConnection, &sqllen);

		auto query = DBQueryHelper::buildUpdateQuery(T::GetTableName(), columnNames, primaryKeyNames);
		if (!dbConnection->Execute(query.c_str())) {
			return;
		}
	}
};

