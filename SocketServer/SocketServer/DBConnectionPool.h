#pragma once
#include "DBConnection.h"

class DBConnectionGaurd
{
private:
	DBConnection* dbConnection;
public:
	DBConnectionGaurd(DBConnection* dbConnection) : dbConnection(dbConnection) {
	}

	~DBConnectionGaurd();

	DBConnection* GetConnection() {
		return dbConnection;
	}
};

/*-------------------
	DBConnectionPool
--------------------*/
class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

	bool					Connect(int32 connectionCount, const WCHAR* connectionString);
	void					Clear();

	DBConnectionGaurdRef		Pop();
	void					Push(DBConnection* connection);

private:
	USE_LOCK;
	SQLHENV					_environment = SQL_NULL_HANDLE;
	Vector<DBConnection*>	_connections;
};
