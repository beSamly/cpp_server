#pragma once
#include "ColumnInfo.h"

class TableInfo
{
private:
	Vector<ColumnInfo> _info;
	function<void()>	MarkAsUpdated = nullptr;

public:
	void SetMarkAsUpdated(function<void()> func) { MarkAsUpdated = func; };

public:
	TableInfo() {}

	TableInfo(ColumnInfo s1, ColumnInfo s2, ColumnInfo s3, ColumnInfo s4, ColumnInfo s5) {
		_info.push_back(s1);
		_info.push_back(s2);
		_info.push_back(s3);
		_info.push_back(s4);
		_info.push_back(s5);
	}

	template<typename T>
	T Get(String columnName) {
		for (auto& columnInfo : _info) {
			if (columnInfo._columnName == columnName) {
				std::shared_ptr<T> ptr = static_pointer_cast<T>(columnInfo._columnValuePtr);
				return *ptr;
			}
		}
	}

	template<typename T>
	void Set(String columnName, T value) {
		for (auto& columnInfo : _info) {
			if (columnInfo._columnName == columnName) {
				std::shared_ptr<T> ptr = static_pointer_cast<T>(columnInfo._columnValuePtr);
				*ptr = value;
				if (MarkAsUpdated != nullptr) {
					MarkAsUpdated();
				}
			}
		}
	}

	ColumnInfoVector GetColumnInfo() {
		ColumnInfoVector infoVector;
		infoVector._vector = _info;
		return infoVector;
	}

	ColumnInfoVector GetInsertInto() {
		ColumnInfoVector infoVector;

		for (auto& columnInfo : _info) {
			if (columnInfo._constraint != Constraint::AUTO_GENERATED) {
				infoVector.AddColumnInfo(columnInfo);
			}
		}

		return infoVector;
	}

	ColumnInfoVector GetUpdateInfo() {

		ColumnInfoVector infoVector;

		for (auto& columnInfo : _info) {
			if (columnInfo._constraint != Constraint::PRIMARY_KEY &&
				columnInfo._constraint != Constraint::UNIQUE_KEY &&
				columnInfo._constraint != Constraint::AUTO_GENERATED
				) {
				infoVector.AddColumnInfo(columnInfo);
			}
		}

		return infoVector;
	}

	ColumnInfoVector GetPrimaryKeyInfo() {
		ColumnInfoVector infoVector;

		for (auto& columnInfo : _info) {
			if (columnInfo._constraint == Constraint::PRIMARY_KEY || columnInfo._constraint == Constraint::UNIQUE_KEY) {
				infoVector.AddColumnInfo(columnInfo);
			}
		}

		return infoVector;
	}

	int32 GetUniqueKey() {
		ColumnInfoVector infoVector;

		for (auto& columnInfo : _info) {
			if (columnInfo._constraint == Constraint::UNIQUE_KEY) {
				return *static_pointer_cast<int32>(columnInfo._columnValuePtr);
			}
		}
	}

	void CopyValue(ColumnInfoVector& columnInfoVector) {
		for (auto& info : _info) {
			auto target = columnInfoVector.Find(info._columnName);
			info.CopyValue(target._columnValuePtr);
		}
	}
};

