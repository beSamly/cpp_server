#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"

class Account : public DBModel<Account>
{
private:
	String ACCOUNT_ID = L"AccountId";
	String EMAIL = L"Email";
	String PASSWORD = L"Password";
	String IS_ADMIN = L"IsAdmin";
	String CREATED_AT = L"CreatedAt";

	String ACCOUNT_TABLE_NAME = L"Account";

private:
	TableSchema _info{
		ColumnInfo(ACCOUNT_ID, ColumnDataType::INT32, Constraint::PRIMARY_KEY),
		ColumnInfo(EMAIL, ColumnDataType::STRING, Constraint::UNIQUE_KEY),
		ColumnInfo(PASSWORD, ColumnDataType::STRING),
		ColumnInfo(IS_ADMIN, ColumnDataType::BOOL) ,
		ColumnInfo(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT, Constraint::AUTO_GENERATED)
	};

public:
	/* Getter Setter */
	int32				GetAccountId() { return _info.Get<int32>(ACCOUNT_ID); };
	String				GetEmail() { return _info.Get<String>(EMAIL); };
	String				GetPassword() { return _info.Get<String>(PASSWORD); };
	bool				GetIsAdmin() { return _info.Get<bool>(IS_ADMIN); };
	TIMESTAMP_STRUCT	GetCreatedAt() { return _info.Get<TIMESTAMP_STRUCT>(CREATED_AT); };

public:
	Account() {

	};

public:
	/* 인터페이스 구현 */
	TableSchema* GetTableSchema() { return &_info; }
	String GetTableName() { return ACCOUNT_TABLE_NAME; };

public:
	/* ORM 함수 */
	AccountRef FindOneByEmail(String email);
};

