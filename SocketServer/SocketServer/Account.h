#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "Column.h"

class Account : public DBModel<Account>
{
private:
	String ACCOUNT_ID = L"AccountId";
	String EMAIL = L"Email";
	String PASSWORD = L"Password";
	String IS_ADMIN = L"IsAdmin";
	String CREATED_AT = L"CreatedAt";

	String TABLE_NAME = L"Account";

	TableSchema _data{
		{
			Column(ACCOUNT_ID, ColumnDataType::INT32, ColumnConstraint::PRIMARY_KEY),
			Column(EMAIL, ColumnDataType::STRING, ColumnConstraint::UNIQUE_KEY),
			Column(PASSWORD, ColumnDataType::STRING),
			Column(IS_ADMIN, ColumnDataType::BOOL) ,
			Column(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT, ColumnConstraint::AUTO_GENERATED)
		}
	};

public:
	/* Getter Setter */
	int32				GetAccountId() { return _data.GetColumnValue<int32>(ACCOUNT_ID); };
	String				GetEmail() { return _data.GetColumnValue<String>(EMAIL); };
	String				GetPassword() { return _data.GetColumnValue<String>(PASSWORD); };
	bool				GetIsAdmin() { return _data.GetColumnValue<bool>(IS_ADMIN); };
	TIMESTAMP_STRUCT	GetCreatedAt() { return _data.GetColumnValue<TIMESTAMP_STRUCT>(CREATED_AT); };

public:
	Account() {

	};

public:
	/* 인터페이스 구현 */
	TableSchema* GetTableSchema() { return &_data; }
	String GetTableName() { return TABLE_NAME; };

public:
	/* ORM 함수 */
	AccountRef FindOneByEmail(String email);
};

