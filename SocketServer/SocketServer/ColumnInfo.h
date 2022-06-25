#pragma once
#include <sqltypes.h>
#include "ColumnDataType.h"

using std::shared_ptr;

class ColumnInfo {
public:
	String _columnName;
	ColumnDataType _dataType;
	shared_ptr<void> _columnValuePtr;

public:
	ColumnInfo(String columnName, ColumnDataType dataType, shared_ptr<void> columnValuePtr = nullptr) : _columnName(columnName), _dataType(dataType), _columnValuePtr(columnValuePtr) {
	};
};

class ColumnInfoVector {
public:
	Vector<ColumnInfo> _vector;
	void AddColumnInfo(String columnName, ColumnDataType dataType, shared_ptr<void> columnValuePtr = nullptr);
	ColumnInfo Find(String columnName);

	template<typename T>
	T FindValueByColumnName(String columnName) {
		ColumnInfo info = Find(columnName);
		auto ptr = static_pointer_cast<T>(info._columnValuePtr);
		return *ptr;
	}
};

//class ColumnInfo
//{
//public:
//	
//private:
//	Map<String, ColumnDataType> _columnMap;
//	String _tableName;
//
//public:
//	void AddColumnInfo(String columnName, ColumnDataType dataType);
//	void SetTableName(String tableName);
//	String GetTableName();
//	Map<String, ColumnDataType> GetColumnMap();
//};
//
