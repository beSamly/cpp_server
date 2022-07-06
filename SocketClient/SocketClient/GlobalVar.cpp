#include "pch.h"
#include "GlobalVar.h"
#include "Logger.h"
#include "PacketManager.h"
#include "InputHandler.h"

Logger* Log = new Logger();
PacketManager* GPacketManager = new PacketManager();
InputHandler* GInputHandler = new InputHandler();

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GInputHandler->Init();
	}

	~CoreGlobal()
	{
		delete Log;
		delete GPacketManager;
		//SocketUtils::Clear();
	}
} GCoreGlobal;