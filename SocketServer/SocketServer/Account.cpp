#include "pch.h"
#include "Account.h"
#include "ColumnDataType.h"
#include "Column.h"

AccountRef Account::FindOneByEmail(String email)
{
	ColumnVector infoVector;
	infoVector.AddColumn(Column(L"Email", email));
	return DBModel::FindOne(infoVector);
}


