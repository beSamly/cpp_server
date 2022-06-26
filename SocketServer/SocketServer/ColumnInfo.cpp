#include "pch.h"
#include "ColumnInfo.h"
#include "ColumnDataType.h"

void ColumnInfoVector::AddColumnInfo(String columnName, ColumnDataType dataType, std::shared_ptr<void> columnValuePtr) {
	ColumnInfo info(columnName, dataType, columnValuePtr);
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
