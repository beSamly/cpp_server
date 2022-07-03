#pragma once
#include "DBConnection.h"
#include "DBModel.h"
#include "ColumnInfo.h"

class Account : public DBModel<Account>
{
private:
	int32				_accountId;
	String				_email;
	String				_password;
	bool				_isAdmin;
	TIMESTAMP_STRUCT	_createdAt;

public:
	Account(ColumnInfoVector& columnInfo);
	Account() {
		// TImeStampHelper 생성
		TIMESTAMP_STRUCT now;
		now.fraction = 0;
		now.hour = 0;
		now.minute = 0;
		now.second = 0;
		now.year = 2022;
		now.month = 11;
		now.day = 13;
		_createdAt = now;
	};

public:
	/* Getter Setter */
	String GetPassword() { return _password; };
	int32 GetAccountId() { return _accountId; };
	//void SetStar(int32 star) { _star = star; };


public:
	/* 인터페이스 구현 */
	ColumnInfoVector	GetUpdateInfo();
	ColumnInfoVector	GetPrimaryKeyInfo();
	int32				GetUniqueKey();

	/* Static methods */
	static ColumnInfoVector GetColumnInfo();
	static String GetTableName();

public:
	/* ORM 함수 */
	static AccountRef FindOneByEmail(String email);
};

