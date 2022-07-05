#pragma once
#include "DBQueryHelper.h"
#include "DBConnection.h"

class DBQueryHelper
{
public:
	static String GetColumnClause(Vector<String> columnNames) {
		String columnClause;
		for (auto& name : columnNames) {
			columnClause += (name + L",");
		}
		columnClause = columnClause.substr(0, columnClause.size() - 1);
		return columnClause;
	}

	static String GetValueClause(int32 count) {
		String valueClause;
		for (int32 i = 0; i < count; i++) {
			valueClause += L"?,";
		}

		valueClause = valueClause.substr(0, valueClause.size() - 1);
		return valueClause;
	}

	static String GetConditionClause(Vector<String> columnNames) {
		String columnClause;
		for (auto& name : columnNames) {
			columnClause += (name + L"=(?) AND ");
		}
		columnClause = columnClause.substr(0, columnClause.size() - 4);
		return columnClause;
	}

	static String GetSetClause(Vector<String> columnNames) {
		String setClause;
		for (auto& name : columnNames) {
			setClause += (name + L"=?, ");
		}
		setClause = setClause.substr(0, setClause.size() - 2);
		return setClause;
	}

	static String buildInsertQuery(String tableName, Vector<String> columnNames) {

		String columnClause = GetColumnClause(columnNames);
		String valueClause = GetValueClause(columnNames.size());
		return std::format(L"INSERT INTO [dbo].[{}]({}) VALUES({})", tableName, columnClause, valueClause);
	};

	static String buildSelectQuery(String tableName, Vector<String> columnNames, Vector<String> keyNames) {
		String columnClause = GetColumnClause(columnNames);
		String conditionClause = GetConditionClause(keyNames);
		return std::format(L"SELECT {} FROM [dbo].[{}] WHERE {}", columnClause, tableName, conditionClause);
	}

	static String buildUpdateQuery(String tableName, Vector<String> columnNames, Vector<String> keyNames) {
		String setClause = GetSetClause(columnNames);
		String conditionClause = GetConditionClause(keyNames);
		return std::format(L"UPDATE [dbo].[{}] SET {} WHERE {}", tableName, setClause, conditionClause);
	};

	static String buildDeleteQuery(String tableName, Vector<String> keyNames) {
		String conditionClause = GetConditionClause(keyNames);
		return std::format(L"DELETE FROM [dbo].[{}] WHERE {}", tableName, conditionClause);
	};

	static void BindCol(ColumnVector* columnInfo, DBConnection* dbConnection, SQLLEN* sqllen) {
		BindInfo(columnInfo, dbConnection, true, sqllen);
	}
	static void BindParam(ColumnVector* columnInfo, DBConnection* dbConnection, SQLLEN* sqllen) {
		BindInfo(columnInfo, dbConnection, false, sqllen);
	}

	static void BindInfo(ColumnVector* columnInfo, DBConnection* dbConnection, bool isColumnBinding, SQLLEN* sqllen) {
		int32 count = 1;

		for (const Column& info : columnInfo->_vector)
		{
			auto columnName = info._columnName;
			auto dataType = info._dataType;
			BindByTypes(dbConnection, isColumnBinding, count, dataType, info._columnValuePtr, sqllen);
			count++;
		}
	}

	static void BindByTypes(DBConnection* dbConnection, bool isColumnBinding, int32 index, ColumnDataType dataType, std::shared_ptr<void> ptr, SQLLEN* sqllen) {

		if (isColumnBinding) {
			switch (dataType) {
			case ColumnDataType::INT32:
				dbConnection->BindCol(index, static_pointer_cast<int32>(ptr).get(), sqllen);
				break;
			case ColumnDataType::TIMESTAMP_STRUCT:
				dbConnection->BindCol(index, static_pointer_cast<TIMESTAMP_STRUCT>(ptr).get(), sqllen);
				break;
			case ColumnDataType::BOOL:
				dbConnection->BindCol(index, static_pointer_cast<bool>(ptr).get(), sqllen);
				break;
			case ColumnDataType::STRING:
				dbConnection->BindCol(index, static_pointer_cast<WCHAR[]>(ptr).get(), sqllen);
				break;
			}
		}
		else {
			switch (dataType) {
			case ColumnDataType::INT32:
				dbConnection->BindParam(index, static_pointer_cast<int32>(ptr).get(), sqllen);
				break;
			case ColumnDataType::TIMESTAMP_STRUCT:
				dbConnection->BindParam(index, static_pointer_cast<TIMESTAMP_STRUCT>(ptr).get(), sqllen);
				break;
			case ColumnDataType::BOOL:
				dbConnection->BindParam(index, static_pointer_cast<bool>(ptr).get(), sqllen);
				break;
			case ColumnDataType::STRING:
				dbConnection->BindParam(index, static_pointer_cast<WCHAR[]>(ptr).get(), sqllen);
				break;
			}
		}
	}
};

