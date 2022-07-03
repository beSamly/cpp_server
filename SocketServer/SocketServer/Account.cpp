#include "pch.h"
#include "Account.h"
#include "ColumnDataType.h"
#include "ColumnInfo.h"

namespace {
	String ACCOUNT_ID = L"AccountId";
	String EMAIL = L"Email";
	String PASSWORD = L"Password";
	String IS_ADMIN = L"IsAdmin";
	String CREATED_AT = L"CreatedAt";

	String ACCOUNT_TABLE_NAME = L"Account";
}

ColumnInfoVector Account::GetColumnInfo() {
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ACCOUNT_ID, ColumnDataType::INT32);
	infoVector.AddColumnInfo(EMAIL, ColumnDataType::STRING);
	infoVector.AddColumnInfo(PASSWORD, ColumnDataType::STRING);
	infoVector.AddColumnInfo(IS_ADMIN, ColumnDataType::BOOL);
	infoVector.AddColumnInfo(CREATED_AT, ColumnDataType::TIMESTAMP_STRUCT);
	return infoVector;
};

String Account::GetTableName() { return ACCOUNT_TABLE_NAME; };

Account::Account(ColumnInfoVector& columnInfo)
{
	_accountId = columnInfo.FindValueByColumnName<int32>(ACCOUNT_ID);
	_email = columnInfo.FindStringValueByColumnName(EMAIL);
	_password = columnInfo.FindStringValueByColumnName(PASSWORD);
	_isAdmin = columnInfo.FindValueByColumnName<bool>(IS_ADMIN);
	_createdAt = columnInfo.FindValueByColumnName<TIMESTAMP_STRUCT>(CREATED_AT);
};

ColumnInfoVector Account::GetPrimaryKeyInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(EMAIL, _email);
	return infoVector;
};

AccountRef Account::FindOneByEmail(String email)
{
	ColumnInfoVector info;
	info.AddColumnInfo(L"Email", email);
	return DBModel::FindOne(info);
}

ColumnInfoVector Account::GetUpdateInfo()
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ACCOUNT_ID, _accountId);
	infoVector.AddColumnInfo(EMAIL, _email);
	infoVector.AddColumnInfo(PASSWORD, _password);
	infoVector.AddColumnInfo(IS_ADMIN, _isAdmin);
	infoVector.AddColumnInfo(CREATED_AT, _createdAt);
	return infoVector;
};

int32 Account::GetUniqueKey() {
	// TODO
	return 1;
};


