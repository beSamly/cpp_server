#include "pch.h"
#include "ColumnInfo.h"
#include "ColumnDataType.h"

void ColumnInfoVector::AddColumnInfo(String columnName, ColumnDataType dataType) {
	std::shared_ptr<void> columnValuePtr = nullptr;
	switch (dataType) {
	case ColumnDataType::INT32:
		columnValuePtr = MakeShared<int32>();
		break;
	case ColumnDataType::TIMESTAMP_STRUCT:
		columnValuePtr = MakeShared<TIMESTAMP_STRUCT>();
		break;
	case ColumnDataType::BOOL:
		columnValuePtr = MakeShared<BOOL>();
		break;
	case ColumnDataType::STRING:
		auto temp = MakeShared<WCHAR[]>(200);
		columnValuePtr = temp;
		break;
	}

	ColumnInfo info(columnName, dataType, columnValuePtr);
	_vector.push_back(info);
}

void ColumnInfoVector::AddColumnInfo(String columnName, String value)
{
	ColumnInfo info(columnName, value);
	_vector.push_back(info);
}

void ColumnInfoVector::AddColumnInfo(String columnName, bool value)
{
	ColumnInfo info(columnName, value);
	_vector.push_back(info);
}

void ColumnInfoVector::AddColumnInfo(String columnName, int32 value)
{
	ColumnInfo info(columnName, value);
	_vector.push_back(info);
}

void ColumnInfoVector::AddColumnInfo(String columnName, TIMESTAMP_STRUCT value)
{
	ColumnInfo info(columnName, value);
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

ColumnInfo::ColumnInfo(String columnName, String value)
{
	_columnName = columnName;
	_dataType = ColumnDataType::STRING;

	// Wstring 을 wchar 로 변경

	auto ptr = MakeShared<WCHAR[]>(value.size());

	//wcsncpy_s();
	wcsncpy_s(ptr.get(), value.size() + 1, value.c_str(), value.size() + 1);
	_columnValuePtr = ptr;
}
