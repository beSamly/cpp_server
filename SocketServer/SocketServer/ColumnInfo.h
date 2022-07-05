#pragma once
#include <sqltypes.h>
#include "ColumnDataType.h"

class ColumnInfo {
public:
	String _columnName;
	ColumnDataType _dataType;
	Constraint _constraint;
	std::shared_ptr<void> _columnValuePtr;

public:
	ColumnInfo(String columnName, ColumnDataType dataType, Constraint constraint = Constraint::NONE);
	ColumnInfo(String columnName, String value);
	ColumnInfo(String columnName, TIMESTAMP_STRUCT value) : _columnName(columnName), _dataType(ColumnDataType::TIMESTAMP_STRUCT), _columnValuePtr(static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>(value))) {};
	ColumnInfo(String columnName, int32 value) : _columnName(columnName), _dataType(ColumnDataType::INT32), _columnValuePtr(static_pointer_cast<void>(MakeShared<int32>(value))) {};
	ColumnInfo(String columnName, bool value) : _columnName(columnName), _dataType(ColumnDataType::BOOL), _columnValuePtr(static_pointer_cast<void>(MakeShared<bool>(value))) {};
	void CopyValue(std::shared_ptr<void> ptr);
};

class ColumnInfoVector {
public:
	Vector<ColumnInfo> _vector;
	void AddColumnInfo(ColumnInfo info);

	ColumnInfo Find(String columnName);

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
