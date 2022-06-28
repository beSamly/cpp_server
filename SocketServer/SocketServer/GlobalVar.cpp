#include "pch.h"
#include "GlobalVar.h"
#include "Logger.h"
#include "PacketManager.h"
#include "DBConnectionPool.h"
#include "PlayerManager.h"
#include "GlobalJobQueue.h"
#include "JobTimer.h"
#include "ThreadManager.h"

Logger* Log = new Logger();
JobTimer* GJobTimer = new JobTimer();
PacketManager* GPacketManager = new PacketManager();
DBConnectionPool* ConnectionPool = new DBConnectionPool();
PlayerManager* GPlayerManager = new PlayerManager();
GlobalJobQueue* GGlobalJobQueue = new GlobalJobQueue();
ThreadManager* GThreadManager = new ThreadManager();

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
		delete GPlayerManager;
		delete GGlobalJobQueue;
		delete GThreadManager;
		delete GJobTimer;
		//SocketUtils::Clear();
	}
} GCoreGlobal;