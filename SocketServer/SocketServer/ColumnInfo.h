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

	ColumnInfo(String columnName, TIMESTAMP_STRUCT value) : _columnName(columnName), _dataType(ColumnDataType::TIMESTAMP_STRUCT), _columnValuePtr(static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>(value))) {
	};

	ColumnInfo(String columnName, int32 value) : _columnName(columnName), _dataType(ColumnDataType::INT32), _columnValuePtr(static_pointer_cast<void>(MakeShared<int32>(value))) {
	};

	ColumnInfo(String columnName, bool value) : _columnName(columnName), _dataType(ColumnDataType::BOOL), _columnValuePtr(static_pointer_cast<void>(MakeShared<bool>(value))) {
	};

	ColumnInfo(String columnName, String value);

};

class ColumnInfoVector {
public:
	Vector<ColumnInfo> _vector;
	void AddColumnInfo(String columnName, ColumnDataType dataType);
	void AddColumnInfo(String columnName, int32 value);
	void AddColumnInfo(String columnName, bool value);
	void AddColumnInfo(String columnName, TIMESTAMP_STRUCT value);
	void AddColumnInfo(String columnName, String value);

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

	String FindStringValueByColumnName(String columnName) {
		ColumnInfo info = Find(columnName);
		auto ptr = static_pointer_cast<WCHAR[]>(info._columnValuePtr);
		return wstring(ptr.get());
	}
};
