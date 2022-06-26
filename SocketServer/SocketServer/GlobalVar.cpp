#include "pch.h"
#include "GlobalVar.h"
#include "Logger.h"
#include "PacketManager.h"
#include "DBConnectionPool.h"
//#include "PlayerManager.h"

Logger* Log = new Logger();
PacketManager* GPacketManager = new PacketManager();
DBConnectionPool* ConnectionPool = new DBConnectionPool();
//PlayerManager* GPlayerManager = new PlayerManager();

class CoreGlobal
{
public:
	CoreGlobal()
	{
		auto connectionString = L"DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;Database=testdb;Trusted_Connection=Yes;";
		ConnectionPool->Connect(500, connectionString);
	}

	~CoreGlobal()
	{
		delete Log;
		delete ConnectionPool;
		//delete GPlayerManager;

		//SocketUtils::Clear();
	}
} GCoreGlobal;