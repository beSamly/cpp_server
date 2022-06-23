#include "pch.h"
#include "GlobalVar.h"
#include "Logger.h"
Logger* Log = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		Log = new Logger();
	}

	~CoreGlobal()
	{
		delete Log;

		//SocketUtils::Clear();
	}
} GCoreGlobal;