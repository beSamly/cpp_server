#pragma once
#include "Column.h"

class TableSchema
{
private:
	Vector<Column> _columns;
	function<void()>	MarkAsUpdated = nullptr;

public:
	void SetMarkAsUpdated(function<void()> func) { MarkAsUpdated = func; };

public:
	TableSchema() {}

	/*TableSchema(Column s1, Column s2, Column s3, Column s4, Column s5) {*/
	TableSchema(Vector<Column> columns) {
		_columns = columns;
		/*_columns.push_back(s1);
		_columns.push_back(s2);
		_columns.push_back(s3);
		_columns.push_back(s4);
		_columns.push_back(s5);*/
	}

	template<typename T>
	T GetColumnValue(String columnName) {
		for (auto& column : _columns) {
			if (column._columnName == columnName) {
				std::shared_ptr<T> ptr = static_pointer_cast<T>(column._columnValuePtr);
				return *ptr;
			}
		}
	}

	template<typename T>
	void SetColumnValue(String columnName, T value) {
		for (auto& column : _columns) {
			if (column._columnName == columnName) {
				std::shared_ptr<T> ptr = static_pointer_cast<T>(column._columnValuePtr);
				*ptr = value;
				if (MarkAsUpdated != nullptr) {
					MarkAsUpdated();
				}
			}
		}
	}

	ColumnVector GetColumn() {
		ColumnVector infoVector;
		infoVector._vector = _columns;
		return infoVector;
	}

	ColumnVector GetInsertInto() {
		ColumnVector infoVector;

		for (auto& column : _columns) {
			if (column._constraint != ColumnConstraint::AUTO_GENERATED) {
				infoVector.AddColumn(column);
			}
		}

		return infoVector;
	}

	ColumnVector GetUpdateInfo() {

		ColumnVector infoVector;

		for (auto& column : _columns) {
			if (column._constraint != ColumnConstraint::PRIMARY_KEY &&
				column._constraint != ColumnConstraint::UNIQUE_KEY &&
				column._constraint != ColumnConstraint::AUTO_GENERATED
				) {
				infoVector.AddColumn(column);
			}
		}

		return infoVector;
	}

	ColumnVector GetPrimaryKeyInfo() {
		ColumnVector infoVector;

		for (auto& column : _columns) {
			if (column._constraint == ColumnConstraint::PRIMARY_KEY || column._constraint == ColumnConstraint::UNIQUE_KEY) {
				infoVector.AddColumn(column);
			}
		}

		return infoVector;
	}

	int32 GetUniqueKey() {
		ColumnVector infoVector;

		for (auto& column : _columns) {
			if (column._constraint == ColumnConstraint::UNIQUE_KEY) {
				return *static_pointer_cast<int32>(column._columnValuePtr);
			}
		}
	}

	void CopyColumnValue(ColumnVector& columnVector) {
		for (auto& info : _columns) {
			auto target = columnVector.Find(info._columnName);
			info.CopyColumnValue(target._columnValuePtr);
		}
	}
};

