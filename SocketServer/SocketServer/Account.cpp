#include "pch.h"
#include "Account.h"
#include "ColumnDataType.h"
#include "ColumnInfo.h"

AccountRef Account::FindOneByEmail(String email)
{
	ColumnInfoVector infoVector;
	infoVector.AddColumnInfo(ColumnInfo(L"Email", email));
	return DBModel::FindOne(infoVector);
}


