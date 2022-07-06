#include "pch.h"
#include "GlobalVar.h"
#include "Logger.h"
#include "PacketManager.h"

Logger* Log = new Logger();
PacketManager* GPacketManager = new PacketManager();

class CoreGlobal
{
public:
	CoreGlobal()
	{
	}

	~CoreGlobal()
	{
		delete Log;
		delete GPacketManager;
		//SocketUtils::Clear();
	}
} GCoreGlobal;