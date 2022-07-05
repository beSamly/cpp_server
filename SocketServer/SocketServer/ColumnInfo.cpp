#include "pch.h"
#include "ColumnInfo.h"
#include "ColumnDataType.h"

ColumnInfo::ColumnInfo(String columnName, ColumnDataType dataType, Constraint constraint)
{
	_columnName = columnName;
	_dataType = dataType;
	_constraint = constraint;

	switch (dataType) {
	case ColumnDataType::INT32:
		_columnValuePtr = static_pointer_cast<void>(MakeShared<int32>());
		break;
	case ColumnDataType::STRING:
		_columnValuePtr = static_pointer_cast<void>(MakeShared<WCHAR[]>(200));
		break;
	case ColumnDataType::TIMESTAMP_STRUCT:
		_columnValuePtr = static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>());
		break;
	}
}

ColumnInfo::ColumnInfo(String columnName, String value)
{
	_columnName = columnName;
	_dataType = ColumnDataType::STRING;

	// Wstring �� wchar �� ����
	auto ptr = MakeShared<WCHAR[]>(value.size());

	//wcsncpy_s();
	wcsncpy_s(ptr.get(), value.size() + 1, value.c_str(), value.size() + 1);
	_columnValuePtr = ptr;
}

void ColumnInfoVector::AddColumnInfo(ColumnInfo info)
{
	_vector.push_back(info);
}

ColumnInfo ColumnInfoVector::Find(String columnName)
{
	for (const auto& columnInfo : _vector) {
		if (columnInfo._columnName == columnName) {
			return columnInfo;
		}
	}
}

void ColumnInfo::CopyValue(shared_ptr<void> ptr)
{
	switch (_dataType) {
	case ColumnDataType::INT32:
		_columnValuePtr = static_pointer_cast<void>(MakeShared<int32>(*static_pointer_cast<int32>(ptr)));
		break;
	case ColumnDataType::STRING: {
		auto tempPtr = static_pointer_cast<WCHAR[]>(ptr);
		String value = wstring(tempPtr.get());
		_columnValuePtr = static_pointer_cast<void>(MakeShared<String>(value));
		break;
	}
	case ColumnDataType::TIMESTAMP_STRUCT:
		_columnValuePtr = static_pointer_cast<void>(MakeShared<TIMESTAMP_STRUCT>(*static_pointer_cast<TIMESTAMP_STRUCT>(ptr)));
		break;
	}
}
