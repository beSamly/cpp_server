#pragma once
#include <sqltypes.h>
#include "ColumnDataType.h"

class Column {
public:
	String _columnName;
	ColumnDataType _dataType;
	ColumnConstraint _constraint;
	std::shared_ptr<void> _columnValuePtr;

public:
	Column(String columnName, ColumnDataType dataType, ColumnConstraint constraint = ColumnConstraint::NONE);
	Column(String columnName, String value);
	Column(String columnName, TIMESTAMP_STRUCT value) : _columnName(columnName), _dataType(ColumnDataType::TIMESTAMP_STRUCT), _columnValuePtr(static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>(value))) {};
	Column(String columnName, int32 value) : _columnName(columnName), _dataType(ColumnDataType::INT32), _columnValuePtr(static_pointer_cast<void>(MakeShared<int32>(value))) {};
	Column(String columnName, bool value) : _columnName(columnName), _dataType(ColumnDataType::BOOL), _columnValuePtr(static_pointer_cast<void>(MakeShared<bool>(value))) {};
	void CopyColumnValue(std::shared_ptr<void> ptr);
};

class ColumnVector {
public:
	Vector<Column> _vector;
	void AddColumn(Column info);

	Column Find(String columnName);

	Vector<String> ExtractKeyNames() {
		Vector<String> columnNames;
		for (const Column& info : _vector) {
			columnNames.push_back(info._columnName);
		}
		return columnNames;
	}

	void Concat(ColumnVector& target) {
		_vector.insert(_vector.end(), target._vector.begin(), target._vector.end());
	}
};
