#pragma once
#include <sqltypes.h>
#include "ColumnDataType.h"

class ColumnInfo {
public:
	String _columnName;
	ColumnDataType _dataType;
	std::shared_ptr<void> _columnValuePtr;

public:
	ColumnInfo(String columnName, ColumnDataType dataType, std::shared_ptr<void> columnValuePtr = nullptr) : _columnName(columnName), _dataType(dataType), _columnValuePtr(columnValuePtr) {
	};
};

class ColumnInfoVector {
public:
	Vector<ColumnInfo> _vector;
	void AddColumnInfo(String columnName, ColumnDataType dataType, std::shared_ptr<void> columnValuePtr = nullptr);
	ColumnInfo Find(String columnName);

	template<typename T>
	T FindValueByColumnName(String columnName) {
		ColumnInfo info = Find(columnName);
		auto ptr = static_pointer_cast<T>(info._columnValuePtr);
		return *ptr;
	}

	Vector<String> ExtractKeyNames() {
		Vector<String> columnNames;
		for (const ColumnInfo& info : _vector) {
			columnNames.push_back(info._columnName);
		}
		return columnNames;
	}

	void Concat(ColumnInfoVector& target) {
		_vector.insert(_vector.end(), target._vector.begin(), target._vector.end());
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
