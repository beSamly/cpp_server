#pragma once
enum class ColumnDataType
{
	INT32,
	TIMESTAMP_STRUCT,
	BOOL,
	STRING
};

enum class ColumnConstraint
{
	NONE,
	UNIQUE_KEY,
	PRIMARY_KEY,
	AUTO_GENERATED,
};
